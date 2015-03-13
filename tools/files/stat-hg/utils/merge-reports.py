import datetime
import optparse
import os
import re
import sys
import xml.sax.saxutils

class MetaXml(xml.sax.ContentHandler):

    def __init__(self, stream):
        xml.sax.ContentHandler.__init__(self)
        self._generator = xml.sax.saxutils.XMLGenerator(stream)
        self._stylesheet_url = None

    def use_stylesheet(self, stylesheet_url):
        self._stylesheet_url = stylesheet_url

    def start(self, project_name):
        self._generator.startDocument()
        if self._stylesheet_url:
            self._generator.processingInstruction(
                'xml-stylesheet',
                'type="text/xsl" href="%s"' % self._stylesheet_url)
        self._generator.startElement(
            'report', {
                'project-name': project_name,
                'date': datetime.datetime.now().strftime('%Y-%m-%d %H:%m:%S'),
            })

    def end(self):
        self._generator.endElement('report')
        self._generator.endDocument()

    def startDocument(self):
        pass

    def endDocument(self):
        pass

    def startElement(self, name, attrs):
        self._generator.startElement(name, attrs)

    def endElement(self, name):
        self._generator.endElement(name)

    def characters(self, data):
        self._generator.characters(data)

    def processingInstruction(self, target, data):
        pass


if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <project-name> <xml-file> ... [options]')
    parser.add_option('', '--out', dest='file', default='',
        help='write to <FILE> instead of STDOUT')
    parser.add_option('', '--xslt', dest='xslt', default='',
        help='link the specified stylesheet')
    (options, args) = parser.parse_args()

    if len(args) < 2:
        parser.error("incorrect number of arguments")

    project_name = args[0]
    xml_file_paths = args[1:]

    if options.file:
        out_stream = open(options.file, 'w')
    else:
        out_stream = sys.stdout

    meta_xml = MetaXml(out_stream)

    if options.xslt:
        meta_xml.use_stylesheet(options.xslt)

    meta_xml.start(project_name)
    for path in xml_file_paths:
        xml.sax.parse(path, meta_xml)
    meta_xml.end()
