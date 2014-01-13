import collections
import csv
import datetime
import optparse
import os.path
import sys
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


class Stats(object):

    def __init__(self, path, lines):
        self.path = path
        self.lines = lines
        self.complexity = { }
        self.statements = { }
        self.maximum_block_depth = { }
        self.calls = { }

    def method(self, name, complexity, statements, maximum_block_depth, calls):
        self.complexity[name] = complexity
        self.statements[name] = statements
        self.maximum_block_depth[name] = maximum_block_depth
        self.calls[name] = calls


class Outlier(object):

    def __init__(self, metric, value, threshold):
        self.metric = metric
        self.value = value
        self.threshold = float(threshold)
        if value > threshold:
            self.score = value / self.threshold
        else:
            self.score = 0
        self.has_details = False


class NamedOutliers(dict):

    def __init__(self, metric, items, threshold):
        self.metric = metric
        self.threshold = float(threshold)
        self.details = {}
        for name, value in items.items():
            if value > threshold:
                self.details[name] = value
        self.score = sum(self.details.values()) / self.threshold
        self.has_details = True


class Toxicity(object):

    def __init__(self, stats):
        self.path = stats.path
        self.outliers = []
        if MAX_LINES:
            self.outliers.append(
                Outlier('lines', stats.lines, MAX_LINES))
        if MAX_COMPLEXITY:
            self.outliers.append(
                NamedOutliers('complexity', stats.complexity, MAX_COMPLEXITY))
        if MAX_STATEMENTS:
            self.outliers.append(
                NamedOutliers('statements', stats.statements, MAX_STATEMENTS))
        if MAX_MAXIMUM_BLOCK_DEPTH:
            self.outliers.append(
                NamedOutliers('maximum-block-depth', stats.maximum_block_depth,
                    MAX_MAXIMUM_BLOCK_DEPTH))
        if MAX_CALLS:
            self.outliers.append(
                NamedOutliers('calls', stats.calls, MAX_CALLS))
        self.score = sum([x.score for x in self.outliers])


class Report(object):

    def __init__(self, stream):
        self._stream = stream

    def use_sheet(self, sheet):
        self._write('<?xml-stylesheet type="text/xsl" href="%s"?>' % sheet)

    def start(self, project_name=None, project_version=None, tool=None):
        self._open(
            'toxicity',
            {
                'project-name': project_name,
                'project-version': project_version,
                'tool': tool,
                'date': datetime.datetime.now().strftime('%Y-%m-%d %H:%m:%S'),
            })

    def add_thresholds(self, thresholds):
        self._open('thresholds', {})
        for threshold in thresholds:
            metric, level, value = threshold
            if not value:
                continue
            self._open(
                'threshold',
                {
                    'metric': metric,
                    'level': level,
                    'value': value
                })
            self._close('threshold')
        self._close('thresholds')

    def start_chart(self):
        self._open('files', {})

    def add_toxicity(self, toxicity):
        self._open(
            'file',
            {
                'path': toxicity.path,
                'toxicity': toxicity.score
            })
        for outliers in toxicity.outliers:
            self._add_outliers(outliers)
        self._close('file')

    def _add_outliers(self, outliers):
        tag = outliers.metric
        toxicity = outliers.score
        if outliers.has_details:
            self._open(tag, {'toxicity': toxicity})
            self._add_details(outliers.details)
            self._close(tag)
        else:
            self._open(tag, {'toxicity': toxicity, 'value': outliers.value})
            self._close(tag)

    def _add_details(self, details):
        for name, value in details.items():
            self._open('method', {'name': name, 'value': value})
            self._close('method')

    def end_chart(self):
        self._close('files')

    def end(self):
        self._close('toxicity')

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
        return xml.sax.saxutils.quoteattr(str(value))


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
    parser.add_option('', '--out', dest='file', default='',
        help='write to <FILE> instead of STDOUT')
    (options, args) = parser.parse_args()

    if len(args) != 2:
        parser.error("incorrect number of arguments")

    stats = { }

    # scan the project-details csv report
    with open(args[0], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            # skip headers
            if n < 1:
                continue
            file_name = record[3]
            if file_name == 'SUMMARY':
                continue
            #~ statements = int(record[5])
            #~ classes_defined = int(record[8])
            lines = int(record[4])
            stats[file_name] = Stats(file_name, lines)

    # scan the method-metrics csv report
    with open(args[1], 'rb') as project_file:
        recordset = csv.reader(project_file)
        for n, record in enumerate(recordset):
            # skip headers
            if n < 1:
                continue
            method_ = record[4]
            complexity = int(record[5].strip('*'))
            statements = int(record[6])
            maximum_block_depth = int(record[7])
            calls = int(record[8])
            stats[record[3]].method(
                method_, complexity, statements, maximum_block_depth, calls)

    toxicities = [Toxicity(s) for s in stats.values()]

    if options.file:
        report_stream = open(options.file, 'w')
    else:
        report_stream = sys.stdout

    report = Report(report_stream)

    if options.xslt:
        report.use_sheet(options.xslt)

    report.start(options.name, options.version, 'SourceMonitor')

    report.add_thresholds([
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

    toxicities = sorted(toxicities, key=lambda t: t.score, reverse=True)

    for i, toxicity in enumerate(toxicities):
        if i == toxicities_to_report:
            break
        if toxicity.score == 0:
            break
        report.add_toxicity(toxicity)

    report.end_chart()
    report.end()
