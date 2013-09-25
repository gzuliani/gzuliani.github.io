import ctypes
import sys

class FnCall(object):

    def __init__(self, line):
        self.id, self.parent, self.addr, self.elapsed = line.split()
        if self.elapsed == "N/A":
            self.elapsed = None
        else:
            self.elapsed = float(self.elapsed)

    def isCompleted(self):
        return self.elapsed is not None


class FnStats(object):

    def __init__(self, fnCall):
        self.hits = 0
        self.failures = 0
        self.fastest = 0
        self.slower = 0
        self.total = 0
        self.add(fnCall)

    def add(self, fnCall):

        if fnCall.isCompleted():
            if self.hits:
                self.fastest = min(self.fastest, fnCall.elapsed)
                self.slower = max(self.slower, fnCall.elapsed)
            else:
                self.fastest = fnCall.elapsed
                self.slower = fnCall.elapsed
            self.total = self.total + fnCall.elapsed;
        else:
            self.failures = self.failures + 1
        self.hits = self.hits + 1

    def __repr__(self):
        return "%d\t%d\t%.3f\t%.3f\t%.3f" % (
            self.hits, self.failures, self.fastest, self.slower, self.total)


class StatsBuilder(object):

    def __init__(self, path):
        skip = 1
        self.stats = {}
        for line in open(sys.argv[1]):
            if skip > 0:
                skip = skip - 1
            else:
                fnCall = FnCall(line)
                if not fnCall.addr in self.stats:
                    self.stats[fnCall.addr] = FnStats(fnCall)
                else:
                    self.stats[fnCall.addr].add(fnCall)

class Dbghelp(object):

    dll = ctypes.WinDLL("Dbghelp.dll")

    UNDNAME_32_BIT_DECODE = 0x0800
    UNDNAME_COMPLETE = 0x0000
    UNDNAME_NAME_ONLY = 0x1000
    UNDNAME_NO_ACCESS_SPECIFIERS = 0x0080
    UNDNAME_NO_ALLOCATION_LANGUAGE = 0x0010
    UNDNAME_NO_ALLOCATION_MODEL = 0x0008
    UNDNAME_NO_ARGUMENTS = 0x2000
    UNDNAME_NO_CV_THISTYPE = 0x0040
    UNDNAME_NO_FUNCTION_RETURNS = 0x0004
    UNDNAME_NO_LEADING_UNDERSCORES = 0x0001
    UNDNAME_NO_MEMBER_TYPE = 0x0200
    UNDNAME_NO_MS_KEYWORDS = 0x0002
    UNDNAME_NO_MS_THISTYPE = 0x0020
    UNDNAME_NO_RETURN_UDT_MODEL = 0x0400
    UNDNAME_NO_SPECIAL_SYMS = 0x4000
    UNDNAME_NO_THISTYPE = 0x0060
    UNDNAME_NO_THROW_SIGNATURES = 0x0100

    def UnDecorateSymbolName(cls, name):
        buffer = ctypes.create_string_buffer(4096)
        result = cls.dll.UnDecorateSymbolName(
            name, buffer, 4096, cls.UNDNAME_NAME_ONLY)
        return buffer.value

    UnDecorateSymbolName = classmethod(UnDecorateSymbolName)


class MapFile(object):

    def __init__(self, path):
        header = True
        self.map = { }
        for line in open(path):
            if header:
                header = not "Rva+Base" in line
            else:
                line = line.strip()

                if not line:
                    continue

                name, addr = line.split()[1:3]
                self.map[addr] = self._undecorate(name)
               
    def nameFromAddr(self, addr):
        if addr in self.map:
            return self.map[addr]
        else:
            return None

    def _undecorate(self, name):
        if name.startswith("__imp_"):
            name = name[6:]
        
        if not name:
            return name

        if name[0] in ['_', '@']:
            name = name[1:]
            pos = name.find('@')
            if pos != -1:
                name = name[:pos]
        elif name[0] == '?':
            name = Dbghelp.UnDecorateSymbolName(name)

        return name


if len(sys.argv) < 2 or len(sys.argv) > 3:
	print "Usage: instrumentation-stats <log-file> [map-file]"
else:
    builder = StatsBuilder(sys.argv[1])

    if len(sys.argv) > 2:
        map = MapFile(sys.argv[2])
        print "addr\tname\thits\texceptions\tmin\tmax\ttotal"
        for addr, stat in builder.stats.items():
            print "%s\t%s\t%d\t%d\t%.3f\t%.3f\t%.3f" % (
                addr, map.nameFromAddr(addr), stat.hits, stat.failures, stat.fastest, stat.slower, stat.total)
    else:
        print "addr\thits\texceptions\tmin\tmax\ttotal"
        for addr, stat in builder.stats.items():
            print "%s\t%d\t%d\t%.3f\t%.3f\t%.3f" % (
                addr, stat.hits, stat.failures, stat.fastest, stat.slower, stat.total)

