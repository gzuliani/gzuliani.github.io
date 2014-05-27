HG_BIN = 'hg.exe'

import optparse
import os
import subprocess
import sqlite3
import sys

hg_repo_base_dir = '.'

def run(cmd, args):
    return subprocess \
        .Popen(' '.join([HG_BIN, cmd, args]), stdout=subprocess.PIPE) \
            .communicate()[0]

def log(args):
    return run('log', args)

def status(args):
    return run('status', args)

def diff(args):
    return run('diff', args)

def get_last_rev():
    return int(log('-l 1 --template "{rev}"'))

def get_changes(rev):
    return status('--change %d' % rev)

def get_diff(rev, path):
    return diff('--change %d %s' % (rev, os.path.join (repo_dir, path)))


class Changeset(object):
    template = '{rev}|{node|short}|{date|isodatesec}|{author}|{tags}|{desc}'

    def __init__(self, data):
        tokens = data.split('|')
        assert len(tokens) == 6
        self.rev = int(tokens[0])
        self.node = tokens[1]
        self.date = tokens[2]
        self.user = tokens[3]
        self.tags = tokens[4]
        self.desc = tokens[5]

    def __repr__(self):
        return '%d|%s|%s|%s|%s|%s' % (
            self.rev, self.node, self.date, self.user, self.tags, self.desc)

def get_changeset(rev):
    return Changeset(log('-r %d --template "%s"' % (rev, Changeset.template)))


class Change(object):

    def __init__(self, rev, data):
        self.rev = rev
        tokens = data.split(' ', 1)
        assert len(tokens) == 2
        self.action = tokens[0]
        assert len(self.action) == 1
        self.path = tokens[1]
        self.count_()

    files_to_count_lines_for = [
        # source files
        '.h', '.hpp',
        '.c', '.cpp',
        '.rc', '.xrc', '.def',
        '.cs',
        '.py',
        # make files
        '.mk',
        # script files
        '.cmd',
        '.iss',
        # text files - may not be line based!
        # '.txt', '.md',
        # '.html', '.htm', '.css',
    ]

    def count_(self):
        self.ins_lines = None
        self.del_lines = None
        name, extension = os.path.splitext(self.path.lower())
        if extension in Change.files_to_count_lines_for:
            diff = get_diff(self.rev, self.path)
            self.ins_lines = diff.count('\n+')
            self.del_lines = diff.count('\n-')
            if self.ins_lines > 0: self.ins_lines = self.ins_lines - 1
            if self.del_lines > 0: self.del_lines = self.del_lines - 1

    def __repr__(self):
        return '%d|%s|%s|%d|%d' % (
            self.rev, self.action, self.path, self.ins_lines, self.del_lines)


if __name__ == '__main__':

    parser = optparse.OptionParser(usage='usage: %prog <repo-dir> <db-file>')
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("incorrect number of arguments")

    repo_dir = args[0]

    connection = sqlite3.connect(args[1])
    cursor = connection.cursor()

    cursor.execute(
        """create table changeset (
            id integer,
            node text,
            date text,
            user text,
            tag text,
            desc text)""");

    cursor.execute(
        """create table change (
            id integer primary key,
            changeset_id integer,
            action text,
            path text,
            ins_lines integer,
            del_lines integer,
            foreign key(changeset_id) references changeset(id))""");

    last_rev = get_last_rev()
    for rev in xrange(last_rev + 1):
        sys.stdout.write(
            '\rloading revision %d/%d, %d%% done...' % (
                rev, last_rev, rev * 100 / last_rev))
        changeset = get_changeset(rev)
        cursor.execute(
            'insert into changeset values (?, ?, ?, ?, ?, ?)', (
                changeset.rev,
                changeset.node,
                changeset.date,
                changeset.user,
                changeset.tags,
                changeset.desc))
        report = get_changes(rev).split('\n')
        for change in [Change(rev, line) for line in report if line]:
            cursor.execute(
                'insert into change values (?, ?, ?, ?, ?, ?)', (
                    None,
                    changeset.rev,
                    change.action,
                    change.path,
                    change.ins_lines,
                    change.del_lines))
    sys.stdout.write('\n')

    cursor.execute(
        "create virtual table tag_cloud using fts4(message)")
    cursor.execute(
        "create virtual table tag_cloud_aux using fts4aux(tag_cloud)")
    cursor.execute(
        "insert into tag_cloud select desc from changeset")

    connection.commit()
    connection.close()
