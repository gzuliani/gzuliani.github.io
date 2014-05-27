import optparse
import os
import sqlite3
import sys
import xml.sax.saxutils

queries = [
    ('lines-of-code',
    'Number of source lines in a revision.',
    '''
         select
           cs.id rev,
           cs.date date,
           cs.tag tag,
           sum(c.ins_lines - c.del_lines) line_count
          from changeset cs inner join change c on (c.changeset_id <= cs.id)
          group by rev
          order by rev
    ''',
    'csv'),

    ('repository-tags',
    'Churn count per tagged revision.',
    '''
        select
         tags.tagged_id rev,
         cs.tag tag,
         sum(c.ins_lines) ins_lines,
         sum(c.del_lines) del_lines
        from (
         select
          cs1.id id,
          min(cs2.id) tagged_id
         from
          changeset cs1,
          changeset cs2
         where cs2.tag <> '' and cs2.id >= cs1.id
         group by cs1.id) tags
        left join changeset cs
        on tags.tagged_id = cs.id
        left join change c
        on c.changeset_id = tags.id
        group by tags.tagged_id, cs.tag
        having sum(c.ins_lines) not null and sum(c.del_lines) not null
    ''',
    'xml'),

    ('activity',
    'Commit times.',
    '''
        select
         strftime('%Y-%m-%d %H:%M:%S', substr(date, 1, 16), substr(date, 21, 3) || ' hours') commit_time
        from changeset
    ''',
    'csv'),

    ('activity-by-hour-of-day',
    'Commits done at a given hour of day.',
    '''
        select
         strftime('%H', substr(date, 1, 16), substr(date, 21, 3) || ' hours') hour,
         count(1)
        from changeset
        group by hour
    ''',
    'csv'),

    ('activity-by-day-of-week',
    'Commits done on a given day of week (0=Sunday, 1=Monday, ...).',
    '''
        select
         strftime('%w', substr(date, 1, 16), substr(date, 21, 3) || ' hours') day,
         count(1)
        from changeset
        group by day
    ''',
    'csv'),

    ('activity-punchcard',
    'Activity punchcard (0=Sunday, 1=Monday, ...)',
    '''
        select
         strftime('%w', substr(date, 1, 16), substr(date, 21, 3) || ' hours') day,
         strftime('%H', substr(date, 1, 16), substr(date, 21, 3) || ' hours') hour,
         count(1) activity
        from changeset
        group by day, hour
    ''',
    'csv'),

    ('commit-log',
    'Commits done.',
    '''
        select
         id rev,
         user,
         date,
         desc
        from changeset
        order by id
    ''',
    'xml'),

    ('file-count',
    'Number of files per revision.',
    '''
        select
         cs.id rev,
         cs.date date,
         cs.tag tag,
         sum(
          case
           when c.action='A' then 1
           when c.action='R' then -1
           else 0
          end) file_count
        from
         changeset cs
         inner join change c on (c.changeset_id <= cs.id)
        where ins_lines is not null
        group by rev
        order by rev
    ''',
    'csv'),

    ('file-size',
    'Average number of lines per file, per revision.',
    '''
        select
         rev,
         date,
         tag,
         line_count,
         file_count,
         line_count * 1. / file_count
        from (
         select
          cs.id rev,
          cs.date date,
          cs.tag tag,
          sum(c.ins_lines - c.del_lines) line_count,
          sum(
           case
            when c.action='A' then 1
            when c.action='R' then -1
            else 0
          end) file_count
         from
          changeset cs inner join change c on (c.changeset_id <= cs.id)
         where ins_lines is not null
         group by rev)
        order by rev
    ''',
    'csv'),

    ('files-with-most-revisions',
    'Files with most revisions.',
    '''
        select
         path,
         count(1) rev_count
        from change
        group by path
        having rev_count >= 10
        order by rev_count desc
        limit 20
    ''',
    'xml'),

    ('loc-and-churn',
    'LOC and churn count, per revision',
    '''
        select
         cs.id rev,
         cs.date date,
         cs.tag tag,
         coalesce(sum(min(c.ins_lines, c.del_lines)), 0) modified,
         coalesce(sum(max(0, c.ins_lines - c.del_lines)), 0) added,
         coalesce(sum(max(0, c.del_lines - c.ins_lines)), 0) removed
        from changeset cs, change c
        where c.changeset_id = cs.id
        group by rev
        order by rev
    ''',
    'csv'),

    ('commit-tag-cloud',
    'Tag cloud of commit messages.',
    '''
        select
         term,
         sum(occurrences) as occurrences,
         length(sum(occurrences)) score
        from tag_cloud_aux
        where
         length(term) > 1
         and cast(term as numeric) = '0'
         and term not in (
          'a', 'about', 'added', 'after', 'all', 'an', 'and', 'as', 
          'by',
          'changeset',
          'does',
          'for',
          'in', 'into', 'is',
          'of', 'on',
          'new', 'not', 'now',
          'some',
          'tag', 'that', 'the', 'to', 'too',
          'when', 'with')
        group by term
        having occurrences > 1
        order by occurrences desc
    ''',
    'xml'),
]


class Table(object):

    def start(self, id, name):
        pass

    def header(self, column_names):
        pass

    def body(self, rows):
        pass


class Tee(Table):

    def __init__(self, left, right):
        self._left = left
        self._right = right

    def start(self, id, name):
        self._left.start(id, name)
        self._right.start(id, name)

    def header(self, column_names):
        self._left.header(column_names)
        self._right.header(column_names)

    def body(self, rows):
        self._left.body(rows)
        self._right.body(rows)


class StdOutLog(Table):

    def start(self, id, name):
        print "building report \"%s\"..." % id


class XmlOutput(Table):

    def __init__(self, stream):
        self._xml = xml.sax.saxutils.XMLGenerator(stream)

    def start(self, id, name):
        self._id = id
        self._name = name

    def header(self, column_names):
        self._column_names = column_names

    def body(self, rows):
        self._open('dataset', {'id': self._id, 'name': self._name})
        for i, row in enumerate(rows):
            self._open('data', {'id': i + 1})
            for j, cell in enumerate(row):
                self._open('prop', {'name': self._column_names[j], 'value': cell})
                self._close('prop')
            self._close('data')
        self._close('dataset')

    def _open(self, name, attrs):
        self._xml.startElement(
            name, dict((n, str(v)) for n, v in attrs.items()))

    def _close(self, name):
        self._xml.endElement(name)


class CsvOutput(Table):

    def __init__(self, stream, sep=','):
        self._stream = stream
        self._sep = sep

    def start(self, id, name):
        pass

    def header(self, column_names):
        self._emit(column_names)

    def body(self, rows):
        for row in rows:
            self._emit(row)

    def _emit(self, record):
        self._stream.write(self._sep.join([str(x) for x in record]) + '\n')

if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <db-file> <output-folder>')
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("incorrect number of arguments")

    connection = sqlite3.connect(args[0])
    output_folder = args[1]

    log = StdOutLog()
    cursor = connection.cursor()

    for query in queries:
        id, name, sql, format = query
        stream = sys.stdout
        stream = open(os.path.join(output_folder, id + '.' + format), 'w')
        if format == 'xml':
            dump = XmlOutput(stream)
        elif format == 'csv':
            dump = CsvOutput(stream, '|')
        else:
            raise RuntimeError, 'unknown format "%s"' % format

        table = Tee(log, dump)
        table.start(id, name)
        cursor.execute(sql)
        table.header(list(map(lambda x: x[0], cursor.description)))
        table.body(cursor)

    connection.close()
