--[[
  Mitchell's html/snippets.lua
  Copyright (c) 2006-2008 Mitchell Foral. All rights reserved.

  SciTE-tools homepage: http://caladbolg.net/scite.php
  Send email to: mitchell<att>caladbolg<dott>net

  Permission to use, copy, modify, and distribute this file
  is granted, provided credit is given to Mitchell.
]]--

---
-- Snippets for the html module
module('modules.html.snippets', package.seeall)

_G.snippets[SCLEX_HTML] = {
  t   = '<${1:p}>${0}</${1/^\\s*(\\S+)\\s*/\\1/}>',
  d   = '<div>${0}</div>',
  dc  = '<div class="${1:class}">${0}</div>',
  ds  = '<div style="${1:style}">${0}</div>',
  p   = '<p>${0}</p>',
  pc  = '<p class="${1:class}">${0}</p>',
  ps  = '<p style="${1:style}">${0}</p>',
  s   = '<span>${0}</span>',
  sc  = '<span class="${1:class}">${0}</span>',
  ss  = '<span style="${1:style}">${0}</span>',
  a   = '<a href="${1:url}">${0}</a>',
  an  = '<a name="${1:anchor}">${0}</a>',
  img = '<img src="${1:url}" alt="${2:alt_text}"${3: width="${4:}" height="${5:}"} />',
  nb  = '&nbsp;',
  f   = '<form action="${1:url}" method="${2:post}" name="${3:}"${4:id="${5:${2}}"}>\n  ${0}\n</form>',
  res = '<input type="reset" name="${1:}"${2: id="${3:${1}}"} value="${4:button_text}" />',
  sub = '<input type="submit" name="${1:}"${2: id="${3:${1}}"} value="${4:button_text}" />',
  che = '<input type="checkbox" name="${1:}"${2: id="${3:${1}}"} value="${4:${1}}"${5: checked="checked"} />',
  file = '<input type="file" name="${1:}"${2: id="${3:${1}}"} accept="${4:mime_types}" />',
  hid = '<input type="hidden" name="${1:}"${2: id="${3:${1}}"} value="${4:default_value}" />',
  pas = '<input type="password" name="${1:}"${2: id="${3:${1}}"} value="${4:default_value}" />',
  rad = '<input type="radio" name="${1:}"${2: id="${3:${1}}"} value="${4:default_value}"${5: checked="checked"} />',
  tex = '<input type="text" name="${1:}"${2: id="${3:${1}}"} value="${4:default_value}" />',
  ['in'] = '<input type="${1:}" name="${2:}"${3: id="${4:${2}}"} value="${5:}" />',
  lab = '<label for="${1:input_item_id}">${2:Label Text}</label>',
  optg = '<optgroup label="${1:label}">\n  ${0}\n</optgroup>',
  opt = '<option label="${1:label}" value="${2:value}"${3: selected="selected"}>${0}</option>',
  sel = '<select name="${1:}" id="${2:${1}}" size="${3:}"${4: multiple="multiple"}>\n  ${0}\n</select>',
  texa = '<textarea name="${1:}" id="${2:${1}}" rows="${3:}" cols="${4:}">${0}</textarea>',
  fs  = '<fieldset>\n  <legend>${1:}</legend>\n  ${0}\n</fieldset>',
  base = '<base href="${1:}"${2: target="${3:}"} />',
  lin = '<link rel="${1:stylesheet}" type="${2:text/css}" href="${3:style.css}"${4: media="${5:screen}"} />',
  met = '<meta name="${1:name}" content="${2:content}" />',
  strict = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n\n",
  html =
[[<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    ${1:}

    <title>${2:title}</title>
  </head>
  <body>
    ${0}
  </body>
</html>]]
}
