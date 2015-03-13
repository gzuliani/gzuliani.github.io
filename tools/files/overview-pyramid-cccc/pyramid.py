import datetime
import optparse
import xml.sax

class Metrics(xml.sax.ContentHandler):

    def __init__(self):
        xml.sax.ContentHandler.__init__(self)
        self._grab = False
        self._modules = set()
        self._ndc = 0
        self._hh = 0
        self.andc = 0
        self.ahh = 0
        self.noc = 0
        self.nom = 0
        self.cyclo = 0
        self.loc = 0
        self.fanout = 0

    def startElement(self, name, attrs):
        if name == 'name':
            self._grab = True
            self._data = []
        elif name == 'number_of_children':
            self._ndc = self._ndc + int(attrs['value'])
        elif name == 'depth_of_inheritance_tree':
            hh = int(attrs['value'])
            if hh != 1100:
                self._hh = self._hh + hh
        elif name == 'weighted_methods_per_class_unity':
            self.nom = self.nom + int(attrs['value'])
        elif name == 'McCabes_cyclomatic_complexity':
            self.cyclo = self.cyclo + int(attrs['value'])
        elif name == 'lines_of_code':
            self.loc = self.loc + int(attrs['value'])
        elif name == 'fan_out':
            self.fanout = self.fanout + int(attrs['value'])

    def endElement(self, name):
        if name == 'name':
            self._grab = False
            self._modules.add(''.join(self._data))
        elif name == 'module':
            self._module_name = ''
        elif name == 'CCCC_Project':
            self.noc = len(self._modules)
            self.andc = float(self._ndc) / self.noc
            self.ahh = float(self._hh) / self.noc

    def characters(self, data):
        if self._grab:
            self._data.append(data)


if __name__ == '__main__':

    parser = optparse.OptionParser(
        usage='usage: %prog <cccc-xml-file>')
    parser.add_option('', '--nop', dest='nop', default='',
        help='supply the value for the NOP metric')
    parser.add_option('', '--calls', dest='calls', default='',
        help='supply the value for the CALLS metric')
    parser.add_option('', '--name', dest='name', default='',
        help='supply the project\'s name')
    parser.add_option('', '--version', dest='version', default='',
        help='supply the project\'s version number')
    parser.add_option('', '--xslt', dest='xslt', default='',
        help='link the specified stylesheet')
    (options, args) = parser.parse_args()

    if len(args) != 1:
        parser.error("incorrect number of arguments")

    metrics = Metrics()
    xml.sax.parse(args[0], metrics)

    print '<?xml version="1.0" encoding="us-ascii"?>'
    if options.xslt:
        print '<?xml-stylesheet type="text/xsl" href="%s"?>' % options.xslt
    attrs = { }
    attrs["tool"] = "CCCC"
    attrs["date"] = datetime.datetime.now().strftime('%Y-%m-%d %H:%m:%S')
    if options.name:
        attrs["project-name"] = options.name
    if options.version:
        attrs["project-version"] = options.version
    print '<pyramid %s>' % ' '.join(['%s=%s' % (
        name, xml.sax.saxutils.quoteattr(value))
            for name, value in attrs.items()])
    print ' <andc>%f</andc>' % metrics.andc
    print ' <ahh>%f</ahh>' % metrics.ahh
    print ' <nop>%s</nop>' % options.nop
    print ' <noc>%d</noc>' % metrics.noc
    print ' <nom>%d</nom>' % metrics.nom
    print ' <loc>%d</loc>' % metrics.loc
    print ' <cyclo>%d</cyclo>' % metrics.cyclo
    print ' <calls>%s</calls>' % options.calls
    print ' <fanout>%d</fanout>' % metrics.fanout
    print '</pyramid>'
