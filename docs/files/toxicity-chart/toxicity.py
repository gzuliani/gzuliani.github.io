import collections
import csv
import datetime
import optparse
import os.path
import xml.sax.saxutils

# http://erik.doernenburg.com/2008/11/how-toxic-is-your-code/
#
# +---------------------------------+-------------+-----------+
# | Metric                          | Level       | Threshold |
# +---------------------------------+-------------+-----------+
# | File Length                     | file        |       500 |
# | Class Fan-Out Complexity        | class       |        30 |
# | Class Data Abstraction Coupling | class       |        10 |
# | Anon Inner Length               | inner class |        35 |
# | Method Length                   | method      |        30 |
# | Parameter Number                | method      |         6 |
# | Cyclomatic Complexity           | method      |        10 |
# | Nested If Depth                 | statement   |         3 |
# | Nested Try Depth                | statement   |         2 |
# | Boolean Expression Complexity   | statement   |         3 |
# | Missing Switch Default          | statement   |         1 |
# +---------------------------------+-------------+-----------+
#
#~ MAX_LINES = 500
#~ MAX_STATEMENTS = 30
#~ MAX_COMPLEXITY = 10
#~ MAX_MAXIMUM_BLOCK_DEPTH = 3
#~ MAX_CALLS = None
#
#
#
# http://wiki.ros.org/code_quality
#
# +---------------------------------------+--------+--------+-----+-----+
# | Metric                                | Level  | Source | Min | Max |
# +---------------------------------------+--------+--------+-----+-----+
# | Comment to code ratio                 | file   | NASA   | 0.2 | 0.3 |
# |                                       |        | HIS    | 0.2 |     |
# |                                       |        | HIS    | 0.2 |     |
# |                                       |        | UoA    | 0.2 | 0.4 |
# |                                       |        | ROS    | 0.2 |     |
# +---------------------------------------+--------+--------+-----+-----+
# | Cyclomatic complexity                 | method | NASA   |   1 |  10 |
# |                                       |        | HIS    |   1 |  10 |
# |                                       |        | KTH    |   1 |  15 |
# |                                       |        | ROS    |   1 |  15 |
# +---------------------------------------+--------+--------+-----+-----+
# | Number of executable lines            | method | NASA   |   1 |  50 |
# |                                       |        | HIS    |   1 |  50 |
# |                                       |        | HTK    |   1 |  70 |
# |                                       |        | ROS    |   1 |  70 |
# +---------------------------------------+--------+--------+-----+-----+
# | Number of function calls              | method | HIS    |   1 |   7 |
# |                                       |        | KTH    |   1 |  10 |
# |                                       |        | ROS    |   1 |  10 |
# +---------------------------------------+--------+--------+-----+-----+
# | Maximum nesting of control structures | method | HIS    |     |   4 |
# |                                       |        | KTH    |     |   5 |
# |                                       |        | ROS    |     |   5 |
# +---------------------------------------+--------+--------+-----+-----+
# | Estimated static path count           | method | HIS    |   1 |  80 |
# |                                       |        | KTH    |   1 | 250 |
# |                                       |        | ROS    |   1 | 250 |
# +---------------------------------------+--------+--------+-----+-----+
# | Coupling between objects              | class  | NASA   |     |   5 |
# |                                       |        | ROS    |   0 |   5 |
# +---------------------------------------+--------+--------+-----+-----+
# | Number of immediate children          | class  | UoA    |     |  10 |
# |                                       |        | ROS    |   0 |  10 |
# +---------------------------------------+--------+--------+-----+-----+
# | Weighted methods per class            | class  | NASA   |     | 100 |
# |                                       |        | UoA    |   1 |  50 |
# |                                       |        | ROS    |   1 | 100 |
# +---------------------------------------+--------+--------+-----+-----+
# | Deepest level of inheritance          | class  | NASA   |     |   5 |
# |                                       |        | UoA    |     |   5 |
# |                                       |        | ROS    |     |   5 |
# +---------------------------------------+--------+--------+-----+-----+
# | Number of methods available           | class  | NASA   |   1 |  20 |
# |                                       |        | ROS    |   1 |  20 |
# +---------------------------------------+--------+--------+-----+-----+
#
# HIS: Hersteller Initiative Software - Manufacturer's software initiative
# KTH: Royal Institute of Technology, Sweden 
# UoA: University of Akureyri in Iceland 
#
#~ MAX_LINES = 500
#~ MAX_STATEMENTS = 70
#~ MAX_COMPLEXITY = 15
#~ MAX_MAXIMUM_BLOCK_DEPTH = 5
#~ MAX_CALLS = 10
#
#
#
# Steffen Herbold, Jens Grabowski, Stephan Waack
# Calculation and optimization of thresholds for sets of software metrics
# Empirical Software Engineering
# December 2011, Volume 16, Issue 6, pp 812-841
# http://link.springer.com/article/10.1007%2Fs10664-011-9162-z
#
# +---------------------------------+----------+-----------+
# | Metric                          | Language | Threshold |
# +---------------------------------+----------+-----------+
# | Cyclomatic Complexity           | C        |        24 |
# | Cyclomatic Complexity           | C/C++    |        10 |
# | Nested Block Depth              | C/C++    |         5 |
# | Number of Function Calls        | C/C++    |         5 |
# | Number of Statements            | C/C++    |        50 |
# +---------------------------------+----------+-----------+
#
#~ MAX_LINES = 500
#~ MAX_STATEMENTS = 50
#~ MAX_COMPLEXITY = 10
#~ MAX_MAXIMUM_BLOCK_DEPTH = 5
#~ MAX_CALLS = 5
#
#
#
# most tolerant configuration
#
MAX_LINES = 500
MAX_STATEMENTS = 70
MAX_COMPLEXITY = 15
MAX_MAXIMUM_BLOCK_DEPTH = 5
MAX_CALLS = 10


class Toxicity(object):

    def __init__(self):
        self._details = collections.defaultdict(float)

    def lines(self, lines):
        self.register_(lines, MAX_LINES, 'lines')

    def method(self, name, complexity, statements, maximum_block_depth, calls):
        self.register_(complexity, MAX_COMPLEXITY, 'complexity')
        self.register_(statements, MAX_STATEMENTS, 'statements')
        self.register_(maximum_block_depth, MAX_MAXIMUM_BLOCK_DEPTH,
            'maximum-block-depth')
        self.register_(calls, MAX_CALLS, 'calls')

    def sum(self):
        return sum(self._details.values())

    @property
    def details(self):
        return [(label, self._details[label]) for label in [
            'lines',
            'complexity',
            'statements',
            'maximum-block-depth',
            'calls']]

    def register_(self, data, threshold, label):
        if not threshold:
            return
        data = float(data)
        if data > threshold:
            self._details[label] += data / threshold


class Report(object):

    def __init__(self):
        print '<?xml version="1.0" encoding="us-ascii"?>'

    def use_sheet(self, sheet):
        print '<?xml-stylesheet type="text/xsl" href="%s"?>' % sheet

    def start(self, project_name=None, project_version=None, tool=None):
        attrs = {
            "project-name": project_name,
            "project-version": project_version,
            "tool": tool,
            "date": datetime.datetime.now().strftime('%Y-%m-%d %H:%m:%S'),
        }
        print '<toxicity %s>' % \
            ' '.join(['%s=%s' % (name, xml.sax.saxutils.quoteattr(value))
                for name, value in attrs.items() if value])

    def publish_thresholds(self, thresholds):
        print ' <thresholds>'
        for threshold in thresholds:
            metric, level, value = threshold
            if not value:
                continue
            print '  <threshold metric=%s level=%s value=%s/>' % (
                xml.sax.saxutils.quoteattr(str(metric)),
                xml.sax.saxutils.quoteattr(str(level)),
                xml.sax.saxutils.quoteattr(str(value)))
        print ' </thresholds>'

    def start_chart(self):
        print ' <files>'

    def add_file(self, path, toxicity, details):
        print ' <file path=%s toxicity=%s>' % (
            xml.sax.saxutils.quoteattr(str(path)),
            xml.sax.saxutils.quoteattr(str(toxicity)))
        for name, value in details:
            self._add_detail(name, value)
        print ' </file>'

    def _add_detail(self, name, value):
        print '  <%s>%s</%s>' % (name, value, name)

    def end_chart(self):
        print ' </files>'

    def end(self):
        print '</toxicity>'


if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <project-details-csv-file> ' \
              '<method-metrics-csv-file> [options]')
    parser.add_option('', '--name', dest='name', default='',
        help='supply the project\'s name')
    parser.add_option('', '--version', dest='version', default='',
        help='supply the project\'s version number')
    parser.add_option('', '--top', dest='top', default='-1',
        help='output the <TOP> worste files only')
    parser.add_option('', '--xslt', dest='xslt', default='',
        help='link the specified stylesheet')
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("incorrect number of arguments")

    toxicities = collections.defaultdict(Toxicity)

    # parse the project-details csv report
    with open(args[0], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            if n < 1:
                continue
            file_name = record[3]
            #~ statements = record[5]
            #~ classes_defined = int(record[8])
            if file_name == 'SUMMARY':
                continue
            toxicities[file_name].lines(record[4])

    # parse the project-details csv report
    with open(args[1], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            if n < 1:
                continue
            name = record[4]
            complexity = int(record[5].strip('*'))
            statements = int(record[6])
            maximum_block_depth = int(record[7])
            calls = int(record[8])
            toxicities[record[3]].method(
                name, complexity, statements, maximum_block_depth, calls)

    report = Report()

    if options.xslt:
        report.use_sheet(options.xslt)

    report.start(options.name, options.version, 'SourceMonitor')

    report.publish_thresholds([
        ('lines', 'file', MAX_LINES),
        ('complexity', 'method', MAX_COMPLEXITY),
        ('statements', 'method', MAX_STATEMENTS),
        ('maximum-block-depth', 'method', MAX_MAXIMUM_BLOCK_DEPTH),
        ('calls', 'method', MAX_CALLS)])

    report.start_chart()

    if options.top > 0:
        toxicities_to_report = int(options.top)
    else:
        toxicities_to_report = len(toxicities)

    toxicities = sorted(toxicities.items(), key=lambda t: t[1].sum(), reverse=True)

    for i, toxicity in enumerate(toxicities):
        if i == toxicities_to_report:
            break
        path, toxicity = toxicity
        if toxicity.sum() == 0:
            break
        report.add_file(path, toxicity.sum(), toxicity.details)

    report.end_chart()
    report.end()
