--[[
  Gianfranco's cpp/snippets.lua
  Copyright (c) 2009 Gianfranco Zuliani. All rights reserved.

  Permission to use, copy, modify, and distribute this file
  is granted, provided credit is given to Gianfranco.
]]--

---
-- Snippets for the cpp module
module('modules.cpp.snippets', package.seeall)

_G.snippets[SCLEX_CPP] = {
	h  = '#ifndef ${1:GUARD}\r\n#define ${1}\r\n\r\n${0}\r\n#endif // ${1}\r\n',
	n  = 'namespace ${1:name}\r\n{\r\n\r\n${0}\r\n} // namespace ${1}\r\n',
	fn  = '${1:ret_val} ${2:name} (\r\n\t${0})\r\n{\r\n\r\n} // ${2}\r\n\r\n',
	m  = '${1:ret_val} ${2:class}::${3:name} (\r\n\t${0})\r\n{\r\n\r\n} // ${2}::${3}\r\n\r\n',
	dm = '// data members\r\nprivate:\r\n\r\n\t',
	om = '// overriden methods\r\nprotected:\r\n\r\n\t',
	pi = '// public interface\r\npublic:\r\n\r\n\t',
	sm = '// support methods\r\nprotected:\r\n\r\n\t',
	class  = [[
// ############################################################################
//	CLASS ${1:name}

class ${1}
{

// constructor
public:

	${1} ();

// destructor
public:

	~${1} ();

${0}
}; // ${1}
]],
	fwd = [[
// ============================================================================
//	FORWARD DECLARATIONS

	class ${0};
]],
	td = 'typedef ${1:what} ${2:alias};',
	try = [[
try
{
	${0}
}
catch (const ${1:exception}&${2: e})
{
}
]],
	fori = [[
for (${1:type} i = ${2:from}; i < ${3:end}; i++)
{
	${0}
}
]],
	forit = [[
for (${1:type}::iterator i = ${2:container}.begin (); i != ${2}.end (); ++i)
{
	${0}
}
]],
	forcit = [[
for (${1:type}::const_iterator i = ${2:container}.begin (); i != ${2}.end (); ++i)
{
	${0}
}
]],
	foritp = [[
for (${1:type}::iterator i = ${2:container}->begin (); i != ${2}->end (); ++i)
{
	${0}
}
]],
	forcitp = [[
for (${1:type}::const_iterator i = ${2:container}->begin (); i != ${2}->end (); ++i)
{
	${0}
}
]],
}
