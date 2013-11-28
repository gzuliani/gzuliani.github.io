import csv
import optparse
import os.path

file_stats = { }

class Stats(object):

    def __init__(self, noc, loc):
        self.noc = noc
        self.nom = 0
        self.cyclo = 0
        self.calls = 0
        self.loc = loc
        self.classes = set()

    def method(self, name, cyclo, length, depth, calls):
        self.nom = self.nom + 1
        self.cyclo = self.cyclo + cyclo
        self.calls = self.calls + calls
        name = name.replace('...', '&hellip;')
        if '.' in name:
            class_name = name.split('.')[0]
            self.classes.add(class_name)


if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <project-details-csv-file> ' \
              '<method-metrics-csv-file> [options]')
    parser.add_option('', '--andc', dest='andc', default='')
    parser.add_option('', '--ahh', dest='ahh', default='')
    parser.add_option('', '--fanout', dest='fanout', default='')
    parser.add_option('', '--xslt', dest='xslt', default='')
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
            file_stats[file_name] = Stats(classes_defined, lines)

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

    print '<?xml version="1.0" encoding="us-ascii"?>'
    if options.xslt:
        print '<?xml-stylesheet type="text/xsl" href="%s"?>' % options.xslt
    print '<pyramid tool="SourceMonitor">'
    print ' <andc>%s</andc>' % options.andc
    print ' <ahh>%s</ahh>' % options.ahh
    print ' <nop>%s</nop>' % nop
    print ' <noc>%d</noc>' % noc
    print ' <nom>%d</nom>' % nom
    print ' <loc>%d</loc>' % loc
    print ' <cyclo>%d</cyclo>' % cyclo
    print ' <calls>%d</calls>' % calls
    print ' <fanout>%s</fanout>' % options.fanout
    print '</pyramid>'
