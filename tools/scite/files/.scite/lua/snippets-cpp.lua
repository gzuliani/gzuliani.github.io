-- cpp snippets
module('modules.cpp.snippets', package.seeall)

_G.snippets[SCLEX_CPP] = {
	h = '#ifndef ${1:GUARD}\r\n#define ${1}\r\n\r\n${0}\r\n#endif // ${1}\r\n',
	n = 'namespace ${1:name} {\r\n\r\n${0}\r\n} // namespace ${1}\r\n',
}
