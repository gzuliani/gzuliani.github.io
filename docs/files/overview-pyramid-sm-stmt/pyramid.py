import csv
import datetime
import optparse
import os.path
import sys
import xml.sax.saxutils

file_stats = { }


class Stats(object):

    def __init__(self, noc, loc):
        self.noc = noc
        self._init_loc(loc)
        self.nom = 0
        self.cyclo = 0
        self.calls = 0
        self.classes = set()

    def method(self, name, cyclo, length, depth, calls):
        self.nom = self.nom + 1
        self.cyclo = self.cyclo + cyclo
        self.calls = self.calls + calls
        name = name.replace('...', '&hellip;')
        if '.' in name:
            class_name = name.split('.')[0]
            self.classes.add(class_name)

    def _init_loc(self, loc):
        raise NotImplementedError


class StatsWithLoc(Stats):

    def __init__(self, noc, loc):
        Stats.__init__(self, noc, loc)

    def _init_loc(self, loc):
        self.loc = loc


class StatsWithStmtAsLoc(Stats):

    def __init__(self, noc, loc):
        Stats.__init__(self, noc, loc)

    def method(self, name, cyclo, length, depth, calls):
        Stats.method(self, name, cyclo, length, depth, calls)
        self.loc = self.loc + length

    def _init_loc(self, loc):
        self.loc = 0


class XmlReport(object):

    def __init__(self, stream):
        self._stream = stream

    def use_sheet(self, sheet):
        self._write('<?xml-stylesheet type="text/xsl" href="%s"?>' % sheet)

    def start(self, project_name=None, project_version=None, tool=None):
        self._open(
            'pyramid',
            {   
                'project-name': project_name,
                'project-version': project_version,
                'tool': tool,
                'date': datetime.datetime.now().strftime('%Y-%m-%d %H:%m:%S'),
            })  

    def metric(self, name, value):
        self._open(name, {})
        self._write(str(value))
        self._close(name)

    def end(self):
        self._close('pyramid')

    def _open(self, name, attrs):
        self._write(
            '<%s>' %
            ' '.join([name] + ['%s=%s' % (name, self._quote(value))
                    for name, value in attrs.items() if value is not None]))

    def _close(self, name):
        self._write('</%s>' % name)

    def _write(self, data):
        self._stream.write(data)

    def _quote(self, value):
        return xml.sax.saxutils.quoteattr(value)


if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <project-details-csv-file> ' \
              '<method-metrics-csv-file> [options]')
    parser.add_option('', '--stmt', dest='stmt', action='store_true',
        help='replace the LOC value with the statement count')
    parser.add_option('', '--andc', dest='andc', default='',
        help='supply the value for the ANDC metric')
    parser.add_option('', '--ahh', dest='ahh', default='',
        help='supply the value for the AHH metric')
    parser.add_option('', '--fanout', dest='fanout', default='',
        help='supply the value for the FANOUT metric')
    parser.add_option('', '--name', dest='name', default='',
        help='supply the project\'s name')
    parser.add_option('', '--version', dest='version', default='',
        help='supply the project\'s version number')
    parser.add_option('', '--xslt', dest='xslt', default='',
        help='link the specified stylesheet')
    parser.add_option('', '--out', dest='file', default='',
        help='write to <FILE> instead of STDOUT')
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("incorrect number of arguments")

    # parse the project-details csv report
    with open(args[0], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            if n < 1:
                continue
            file_name = record[3]
            if file_name == 'SUMMARY':
                continue
            lines = int(record[4])
            statements = record[5]
            classes_defined = int(record[8])
            if options.stmt:
                stats = StatsWithStmtAsLoc(classes_defined, lines)
            else:
                stats = StatsWithLoc(classes_defined, lines)

            file_stats[file_name] = stats

    # parse the project-details csv report
    with open(args[1], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            if n < 1:
                continue
            file_name = record[3]
            method = record[4]
            cyclo = int(record[5].strip('*'))
            statements = int(record[6])
            maximum_depth = int(record[7])
            calls = int(record[8])
            file_stats[file_name].method(
                method, cyclo, statements, maximum_depth, calls)

    noc = 0
    nom = 0
    loc = 0
    cyclo = 0
    calls = 0
    folders = set()
    for path, stats in file_stats.items():
        folders.add(os.path.basename(os.path.dirname(path)))
        loc = loc + stats.loc
        noc = noc + stats.noc
        nom = nom + stats.nom
        cyclo = cyclo + stats.cyclo
        calls = calls + stats.calls

    nop = len(folders)

    if options.file:
        report_stream = open(options.file, 'w')
    else:
        report_stream = sys.stdout

    report = XmlReport(report_stream)

    if options.xslt:
        report.use_sheet(options.xslt)

    report.start(options.name, options.version, "SourceMonitor")
    report.metric('andc', options.andc)
    report.metric('ahh', options.ahh)
    report.metric('nop', nop)
    report.metric('noc', noc)
    report.metric('nom', nom)
    report.metric('loc', loc)
    report.metric('cyclo', cyclo)
    report.metric('calls', calls)
    report.metric('fanout', options.fanout)
    report.end()
