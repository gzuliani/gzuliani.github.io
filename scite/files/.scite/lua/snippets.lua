--[[
  Mitchell's snippets.lua
  Copyright (c) 2006-2008 Mitchell Foral. All rights reserved.

  SciTE-tools homepage: http://caladbolg.net/scite.php
  Send email to: mitchell<att>caladbolg<dott>net

  Permission to use, copy, modify, and distribute this file
  is granted, provided credit is given to Mitchell.
]]--

---
-- Provides Textmate-like snippets for the scite module.
-- There are several option variables used:
--   PLATFORM: OS platform (linux or windows).
--   MARK_SNIPPET: The integer mark used to identify the line that marks the
--     end of a snippet.
--   SCOPES_ENABLED: Flag indicating whether scopes/styles can be used for
--     snippets.
--   FILE_IN: Location of the temporary file used as STDIN for regex mirrors.
--   FILE_OUT: Location of the temporary file that will contain output for
--     regex mirrors.
--   REDIRECT: The command line symbol used for redirecting STDOUT to a file.
--   RUBY_CMD: The command that executes the Ruby interpreter.
--   MARK_SNIPPET_COLOR: The Scintilla color used for the line
--     that marks the end of the snippet.
module('modules.scite.snippets', package.seeall)

-- Usage:
-- Basically, snippets are pieces of text inserted into a document, but can
-- execute shell code at run-time, contain placeholders for additional
-- information to be added, and make simple transforms on that information.
-- This is much more powerful than SciTE's abbreviation expansion system.
--
-- Syntax:
--   Snippets are defined in a user-defined table 'snippets'. Scopes (discussed
--   below) are numeric indices of the snippets table and are tables themselves.
--   Each string index in each scope table is the snippet trigger text. The
--   expanded text is equated to this trigger.
--
--   For example:
--   snippets = {
--     file = "$(FileNameExt)",
--     [SCLEX_RUBY] = {
--       ['def'] = "def ${1:initialize}(${2:})\n  ${0}\nend"
--       [SCE_RB_STRING] = {
--         ['c'] = "#{${0}}"
--       }
--     }
--   }
--
--   The top-level snippets are global, the SCLEX_RUBY snippets are global to a
--   buffer with Ruby syntax highlighting enabled, and the SCLEX_RUBY
--   SCE_RB_STRING snippet is expanded in that buffer only when currently in
--   Ruby's string scope.
--
--   Scopes and Lexers:
--     In the previous example, SCLEX_RUBY is a constant defining the Ruby lexer
--     and has the value in Scintilla.iface (22). SCE_RB_STRING is the string
--     scope in SCLEX_RUBY whose definition is also in Scintilla.iface (6).
--
--     Scope-insensitive snippets should be placed in the lexer table, and
--     lexer-insensitive key commands should be placed in the keys table.
--
--   By default scopes are enabled. To disable them, set the SCOPES_ENABLED
--   variable to false.
--
--   Order of expansion precidence: Scope, Lexer, Global.
--     Snippets in the current scope have the first priority, snippets in the
--     current lexer have the second, and global snippets have the last
--     priority.
--
--   Declaring snippets: ['snippet_trigger'] = "snippet_text"
--     ( e.g. ['file'] = "$(FileNameExt)" )
--     snippet_trigger is the text used to trigger snippet expansion and
--     snippet_text is the body of the snippet shown upon expansion.
--     snippet_text can contain more than just text:
--
--     Placeholders/tab stops: ${num:text} (e.g. ${1:text})
--       These are visited in numeric order with ${0} being the final cursor
--       position. If the final cursor position is not specified, the cursor is
--       placed at the end of the snippet.
--
--     Mirrors: ${num} (e.g. ${1})
--       ${1} would be mirrored by whatever value ${1:text} is in the above
--       example. Note that mirrors are not updated as text is typed, only after
--       the next item is moved to.
--
--     Transformations: ${num/pattern/replacement/options}
--       (e.g. ${1/text/other $0/})
--       Transformations are like mirrors, only they modify the text to mirror.
--       In this case, 'text' would be replaced with 'other text' if the value
--       of ${1:text} in the example above matched the pattern. The regular
--       expressions are Ruby's regexps. Captures groups are referenced with the
--       prefix '$' and $0 is the entire match. Ruby code can be executed inside
--       the replacement text using #{}. (e.g. ${1/text/#{$0.capitalize}/})
--
--     SciTE variables: $(variable) (e.g. $(FileNameExt))
--       These are expanded like in .properties files.
--
--     Interpolated shell code: `shell_code` (e.g. `date`)
--
--     The '$', '/', '}', and '`' characters can be escaped with the '\'
--     character. Keep in mind that this follows Lua syntax, so in literal
--     strings (" " or ' '), '\\' is equivalent to one '\' character, but in
--     strings like [[ ]], a single '\' is used.
--
-- To expand a trigger word, call the snippets module's 'insert' function.
--
-- Be sure to set the PLATFORM, RUBY_CMD, FILE_IN and FILE_OUT variables as
-- appropriate. Regexps use Ruby, so Ruby must be installed. That, or you can
-- modify the code to use another language's regexps.
-- (Get Ruby at http://ruby-lang.org)
--
-- You can declare snippets in separate lua files and use them. For example, I
-- have a ruby.lua file with snippets specific to Ruby that is loaded whenever I
-- open or switch to a Ruby file, but are otherwise invisible to non-Ruby files.
--
-- Unlike Textmate, you CAN have nested snippets.
--
-- Limitations:
--   Shell code inside regexps is executed the moment a snippet is inserted, not
--     as placeholders are filled.
--   Calling undo or performing other text operations outside the snippet WILL
--     probably cause unexpected behavior.
--   I don't recommend using the TAB key as the trigger word expander. I've
--     tried with mixed success to keep the key's original functionality along
--     with snippet expansion. I happen to use Ctrl+I instead.
--   Apparently you cannot call module functions from a command defined in a
--     SciTE properties file without prepending 'dostring ' first. So something
--     like
--       command.0.*=dostring modules.scite.snippets.insert()
--     will function as expected.
--
-- Bugs:
--   If you come across a bug, please turn the DEBUG variable on and send me
--   both the snippet text and output text.
--
-- Testing:
--   To run the test suite, change the RUN_TESTS flag and reload snippets.lua.
--   Remember to reset the flag when you are finished!

-- options
local PLATFORM = _G.PLATFORM
local MARK_SNIPPET   = 4
local SCOPES_ENABLED = true
local FILE_IN, FILE_OUT, REDIRECT, RUBY_CMD, MARK_SNIPPET_COLOR
local PYTHON_CMD, REDIRECT_STDERR
if PLATFORM == 'linux' then
  FILE_IN  = '/tmp/scite_input'
  FILE_OUT = '/tmp/scite_output'
  REDIRECT = ' &> '
  RUBY_CMD = 'ruby '
  PYTHON_CMD = props['python']..' '
  MARK_SNIPPET_COLOR = tonumber("0x4D9999")
elseif PLATFORM == 'windows' then
  FILE_IN  = os.getenv('TEMP')..'\\scite_input.py'
  FILE_OUT = os.getenv('TEMP')..'\\scite_output.txt'
  REDIRECT = ' > '
  RUBY_CMD = 'ruby '
  PYTHON_CMD = props['python']..' '
  REDIRECT_STDERR = ' 2> '
  MARK_SNIPPET_COLOR = 5085593
end
local DEBUG = false
local RUN_TESTS = false
-- end options

---
-- Global container that holds all snippet definitions.
-- @class table
-- @name snippets
_G.snippets = {}

-- some default snippets
_G.snippets.file = "$(FileNameExt)"
_G.snippets.path = "$(FilePath)"
_G.snippets.tab  = "\${${1:1}:${2:default}}"
_G.snippets.key  = "['${1:}'] = { ${2:func}${3:, ${4:arg}} }"

---
-- [Local table] The current snippet.
-- @class table
-- @name snippet
local snippet = {}

---
-- [Local table] The stack of currently running snippets.
-- @class table
-- @name snippet_stack
local snippet_stack = {}

-- local functions
local next_snippet_item
local snippet_text, match_indention, join_lines, load_scopes
local escape, unescape, remove_escapes, _DEBUG

---
-- Begins expansion of a snippet.
-- @param snippet_arg Optional snippet to expand. If none is specified, the
--   snippet is determined from the trigger word to the left of the caret, the
--   lexer, and scope.
function insert(snippet_arg)
  local orig_pos, new_pos, s_name
  props['SelectedText'] = editor:GetSelText()
  if not snippet_arg then
    orig_pos = editor.CurrentPos editor:WordLeftExtend()
    new_pos  = editor.CurrentPos
    lexer    = editor.Lexer
    scope    = editor.StyleAt[orig_pos]
    s_name   = editor:GetSelText()
  else
    if editor.CurrentPos > editor.Anchor then
      editor.CurrentPos, editor.Anchor = editor.Anchor, editor.CurrentPos
    end
    orig_pos, new_pos = editor.CurrentPos, editor.CurrentPos
  end

  -- Get snippet text by lexer, scope, and/or trigger word.
  local s_text
  if s_name then
    _DEBUG('s_name: '..s_name..', lexer: '..lexer..', scope: '..scope)
    local function try_get_snippet(...)
      local table = _G.snippets
      for _, idx in ipairs(arg) do table = table[idx] end
      if table and type(table) == 'string' then return table end
      error() -- snippet doesn't exist
    end
    local ret
    if SCOPES_ENABLED then
      ret, s_text = pcall(try_get_snippet, lexer, scope, s_name)
    end
    if not ret then ret, s_text = pcall(try_get_snippet, lexer, s_name) end
    if not ret then ret, s_text = pcall(try_get_snippet, s_name) end
  else
    s_text = snippet_arg
  end

  editor:BeginUndoAction()
  if s_text then
    s_text = escape(s_text)
    _DEBUG('s_text escaped:\n'..s_text)

    -- Replace SciTE variables.
    s_text = s_text:gsub( '%$%((.-)%)', function(prop) return props[prop] end )

    -- Execute any shell code.
    s_text = s_text:gsub('`(.-)`',
      function(code)
        os.execute(code..REDIRECT..FILE_OUT)
        local f = io.open(FILE_OUT)
        local out = f:read('*all')
        f:close()
        if out:sub(-1) == '\n' then return out:sub(1, -2) end
      end)

    -- If another snippet is running, push it onto the stack.
    if snippet.index then table.insert(snippet_stack, snippet) end

    snippet = {}
    snippet.snapshots = {}
    snippet.index     = 0
    snippet.start_pos = editor.CurrentPos
    snippet.cursor    = nil
    snippet.sel_text  = props['SelectedText']

    -- Make a table of placeholders and tab stops.
    local patt, patt2 = '($%b{})', '^%${(%d+):.*}$'
    local s, _, item = s_text:find(patt)
    while item do
      local _, _, num = item:find(patt2)
      if num then snippet[ tonumber(num) ] = unescape(item) end
      local i = s + 1
      s, _, item = s_text:find(patt, i)
    end

    s_text = unescape(s_text)
    _DEBUG('s_text unescaped:\n'..s_text)

    -- Insert the snippet and set a mark defining the end of it.
    editor:ReplaceSel(s_text)
    editor:NewLine()
    local line = editor:LineFromPosition(editor.CurrentPos)
    snippet.end_marker = editor:MarkerAdd(line, MARK_SNIPPET)
    --editor:MarkerSetBack(MARK_SNIPPET, MARK_SNIPPET_COLOR)
    _DEBUG('snippet:')
    if DEBUG then table.foreach(snippet, print) end

    -- Indent all lines inserted.
    editor.CurrentPos = new_pos
    local count, i = -1, -1
    repeat
      count = count + 1
      i = s_text:find('\n', i + 1)
    until i == nil
    match_indention( editor:LineFromPosition(orig_pos), count )
  else
    editor:SetSel(orig_pos, orig_pos)
  end
  editor:EndUndoAction()

  next_snippet_item()
end

---
-- [Local function] Mirror or transform most recently modified field in the
-- current snippet and move on to the next field.
next_snippet_item = function()
  if not snippet.index then return end
  local s_start, s_end, s_text = snippet_text()

  -- If something went wrong and the snippet has been 'messed' up
  -- (e.g. by undo/redo commands).
  if not s_text then cancel_current() return end
  snippet.snapshots[snippet.index] = s_text

  -- Mirror and transform.
  editor:BeginUndoAction()
  if snippet.index > 0 then
    if snippet.cursor then
      editor:SetSel(snippet.cursor, editor.CurrentPos)
    else
      editor:WordLeftExtend()
    end
    local last_item = editor:GetSelText()
    _DEBUG('last_item:\n'..last_item)

    editor:SetSel(s_start, s_end)
    s_text = escape(s_text)
    _DEBUG('s_text escaped:\n'..s_text)

    -- Regex mirror.
    patt = '%${'..snippet.index..'/(.-)/(.-)/(.-)}'
    s_text = s_text:gsub(patt,
      function(pattern, replacement, options)
        local script = [[
import re
matches = re.search(r"pattern", "last_item", options)
result = "replacement"
if matches:
    tokens = ["\"" + token.replace("\"", "\\\"") + "\"" for token in matches.groups()]
    for pos, expression in enumerate(re.finditer(r"\#\{(.+?)\}", result)):
        code = expression.group(1).replace(r"\%d" % (pos + 1), tokens[pos])
        result = result.replace(expression.group(0), eval(code))
    print matches.expand(result)
        ]]
        pattern     = unescape(pattern)
        replacement = unescape(replacement)
        escaped_pattern     = string.gsub(pattern, '"', '\\"')
        escaped_replacement = string.gsub(replacement, '\\', '\\\\'):gsub('"', '\\"')
        escaped_last_item   = string.gsub(last_item, '"', '\\"')
        script = script:gsub('last_item', escaped_last_item)
        script = script:gsub('pattern', escaped_pattern)
        if options ~= "" then
          script = script:gsub('options', options)
        else
          script = script:gsub('options', '0')
        end
        script = script:gsub('replacement', escaped_replacement)
        _DEBUG('script:\n'..script)

        local f, out
        -- write the script
        f = io.open(FILE_IN, 'w') f:write(script) f:close()

        -- check the syntax
        os.execute(PYTHON_CMD..'-c "import py_compile; py_compile.compile(\''..FILE_IN..'\')"'..REDIRECT_STDERR..FILE_OUT)
        f = io.open(FILE_OUT) out = f:read('*all') f:close()
        if out:find('SyntaxError') ~= nil then return out end

        -- execute the script
        os.execute(PYTHON_CMD..FILE_IN..REDIRECT..FILE_OUT)
        f = io.open(FILE_OUT) out = f:read('*all') f:close()
        _DEBUG('regex out:\n'..out)

        if out:sub(-1) == '\n' then out = out:sub(1, -2) end
        return out
      end)
    _DEBUG('patterns replaced:\n'..s_text)

    -- Plain text mirror.
    local mirror = '%${'..snippet.index..'}'
    s_text = s_text:gsub(mirror, last_item)
    _DEBUG('mirrors replaced:\n'..s_text)
  else
    s_text = escape(s_text)
    _DEBUG('s_text escaped:\n'..s_text)
  end
  editor:EndUndoAction()

  editor:SetSel(s_start, s_end)

  -- Find next snippet item or finish.
  editor:BeginUndoAction()
  snippet.index = snippet.index + 1
  if snippet[snippet.index] then
    _DEBUG('next index: '..snippet.index)
    local s = s_text:find('${'..snippet.index..':')
    local next_item = s_text:match('($%b{})', s)
    s_text = unescape(s_text)
    _DEBUG('s_text unescaped:\n'..s_text)
    editor:ReplaceSel(s_text)
    if s and next_item then
      next_item = unescape(next_item)
      _DEBUG('next_item:\n'..next_item)
      local s, e = editor:findtext(next_item, 0, s_start)
      if s and e then
        editor:SetSel(s, e)
        snippet.cursor = s
        local patt = '^%${'..snippet.index..':(.*)}$'
        local default = next_item:match(patt)
        editor:ReplaceSel(default)
        editor:SetSel(s, s + #default)
      else
        _DEBUG('search failed:\n'..next_item)
        next_snippet_item()
      end
    else
      _DEBUG('no item for '..snippet.index)
      next_snippet_item()
    end
  else -- finished
    _DEBUG('snippet finishing...')
    s_text = s_text:gsub('${0}', '$CURSOR', 1)
    s_text = unescape(s_text)
    _DEBUG('s_text unescaped:\n'..s_text)
    s_text = remove_escapes(s_text)
    _DEBUG('s_text escapes removed:\n'..s_text)
    editor:ReplaceSel(s_text)
    local _, s_end = snippet_text()
    if s_end then
      -- Compensate for extra char in CR+LF line endings.
      if editor.EOLMode == 0 then s_end = s_end - 1 end
      editor:SetSel(s_end, s_end)
      join_lines()
    end

    local s, e = editor:findtext('$CURSOR', 4, s_start)
    if s and e then
      editor:SetSel(s, e)
      editor:ReplaceSel()
    else
      editor:SetSel(s_end, s_end) -- at snippet end marker
    end
    editor:MarkerDeleteHandle(snippet.end_marker)
    snippet = {}

    -- Restore previous running snippet (if any).
    if #snippet_stack > 0 then snippet = table.remove(snippet_stack) end
  end
  editor:EndUndoAction()
end

---
-- Goes back to the previous placeholder or tab stop, reverting changes made to
-- subsequent ones.
function prev()
  if not snippet.index then return end
  local index = snippet.index
  if index > 1 then
    local s_start, s_end = snippet_text()
    local s_text = snippet.snapshots[index - 2]
    editor:SetSel(s_start, s_end) editor:ReplaceSel(s_text)
    snippet.index = index - 2
    next_snippet_item()
  end
end

---
-- Cancels active snippet, reverting to the state before the snippet was
-- activated.
function cancel_current()
  if not snippet.index then return end
  local s_start, s_end = snippet_text()
  if s_start and s_end then
    editor:SetSel(s_start, s_end)
    editor:ReplaceSel() join_lines()
  end
  if snippet.sel_text then
    editor:AddText(snippet.sel_text)
    editor.Anchor = editor.Anchor - #snippet.sel_text
  end
  editor:MarkerDeleteHandle(snippet.end_marker)
  snippet = {}

  -- Restore previous running snippet (if any).
  if #snippet_stack > 0 then snippet = table.remove(snippet_stack) end
end

---
-- List available snippet triggers as an autocompletion list.
-- Global snippets and snippets in the current lexer and scope are used.
function list()
  local list, list_str = {}, ''

  local function add_snippets(snippets)
    for s_name in pairs(snippets) do print(s_name) table.insert(list, s_name) end
  end

  local snippets = _G.snippets
  add_snippets(snippets)
  if SCOPES_ENABLED then
    local lexer = editor.Lexer
    local scope = editor.StyleAt[editor.CurrentPos]
    if snippets[lexer] and type( snippets[lexer] ) == 'table' then
      add_snippets( snippets[lexer] )
      if snippets[lexer][scope] then add_snippets( snippets[lexer][scope] ) end
    end
  end

  table.sort(list)
  local sep = string.char(editor.AutoCSeparator)
  for _, v in pairs(list) do list_str = list_str..v..sep end
  list_str = list_str:sub(1, -2) -- chop
  editor:AutoCShow(0, list_str)
end

---
-- Show the scope/style at the current caret position as a calltip.
function show_scope()
  if not SCOPES_ENABLED then print('Scopes disabled') return end
  local lexer = editor.Lexer
  local scope = editor.StyleAt[editor.CurrentPos]
  local text = 'Lexer: '..lexer..'\nScope: '..scope
  editor:CallTipShow(editor.CurrentPos, text)
end

---
-- [Local function] Gets the text of the snippet.
-- This is the text bounded by the start of the trigger word to the end snippet
-- marker on the line after the snippet's end.
snippet_text = function()
  local s = snippet.start_pos
  local e = editor:PositionFromLine(
    editor:MarkerLineFromHandle(snippet.end_marker) ) - 1
  if e >= s then return s, e, editor:textrange(s, e) end
end

---
-- [Local function] Replace escaped snippet characters with their octal
-- equivalents.
escape = function(text)
  return text:gsub('\\([$/}`])',
    function(char) return ("\\%03d"):format( char:byte() ) end)
end

---
-- [Local function] Replace octal snippet characters with their escaped
-- equivalents.
unescape = function(text)
  return text:gsub('\\(%d%d%d)',
    function(value) return '\\'..string.char(value) end)
end

---
-- [Local function] Remove escaping forward-slashes from escaped snippet
-- characters.
-- At this point, they are no longer necessary.
remove_escapes = function(text) return text:gsub('\\([$/}`])', '%1') end

---
-- [Local function] When snippets are inserted, match their indentation level
-- with their surroundings.
match_indention = function(ref_line, num_lines)
  if num_lines == 0 then return end
  local isize = editor.Indent
  local ibase = editor.LineIndentation[ref_line]
  local inum  = ibase / isize -- num of indents needed to match
  local line = ref_line + 1
  for i = 0, num_lines - 1 do
    local linei = editor.LineIndentation[line + i]
    editor.LineIndentation[line + i] = linei + isize * inum
  end
end

---
-- [Local function] Joins current line with the line below it, eliminating
-- whitespace.
-- This is used to remove the empty line containing the end of snippet marker.
join_lines = function()
  editor:LineDown() editor:VCHome()
  if editor.Column[editor.CurrentPos] == 0 then
    editor:VCHome()
  end
  editor:HomeExtend()
  if #editor:GetSelText() > 0 then
    editor:DeleteBack()
  end
  editor:DeleteBack()
end

---
-- [Local function] Called for printing debug text if DEBUG flag
-- is set.
-- @param text Debug text to print.
_DEBUG = function(text) if DEBUG then print('---\n'..text) end end

-- run tests
if RUN_TESTS then
  function next_item() next_snippet_item() end
  if not package.path:find(props.SciteDefaultHome) then
    package.path = package.path..';'..props.SciteDefaultHome..'/scripts/'
  end
  require 'utils/test_snippets'
end
