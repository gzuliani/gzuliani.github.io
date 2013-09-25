﻿# Markdown and SciTE

_How to get a live preview (on Firefox) of a markdown file._

Environment:

* Windows 7 SP1 64 bit
* Python 2.6.6
* SciTE 3.2.5

Prerequisites:

* [python markdown](http://pythonhosted.org/Markdown/)

Optional packages:

* [smarty pants](https://pypi.python.org/pypi/mdx_smartypants/1.3), to emit 
  typographically nicer ("curly") quotes, proper ("em" and "en") dashes, etc.;

* [del/ins](https://pypi.python.org/pypi/mdx_del_ins/1.0), to support the `del` 
  and `ins` tags;

 * [xhtml_wrap](https://bitbucket.org/thinkstorm/xhtml_wrap/src), to wrap the
   output in XHTML, optionally adding a title and a CSS URL.

## SciTE setup

* pick up a temporary folder to host the markdown previews, e.g. 
`%UserProfile%\.md` --- put the `markdown.css` file of your choice here;

* define the following variables *before* the inclusion of the lua scripts in 
  your `SciTEUser.properties` file:

        python.home=C:\Python26
        python=$(python.home)\python.exe
        python.scripts.dir=$(python.home)\Scripts
        markdown.rendering.command=1121
        markdown.rendering.dir=$(SciteUserHome)\.md
        markdown.rendering.file=$(markdown.rendering.dir)\$(FileName).html

* to open the markdown preview on the default browser, add these lines:

        command.build.subsystem.$(file.patterns.markdown)=2
        command.build.$(file.patterns.markdown)="$(markdown.rendering.file)"

* to render it automatically at save time:

    * add the following lines to your `SciTEUser.properties` file:

            file.patterns.markdown=*.md;*.markdown
            filter.markdown=Markdown (md markdown)|$(file.patterns.markdown)|
            command.name.21.$(file.patterns.markdown)=
            command.save.before.21.$(file.patterns.markdown)=2
            command.21.$(file.patterns.markdown)=$(python.scripts.dir)\markdown_py.bat -x extra -x del_ins -x meta -x sane_lists -x smartypants -x toc -x wikilinks -x xhtml_wrap(title="",css_url="markdown.css",js_url="") -f "$(markdown.rendering.file)" "$(FilePath)"
            user.shortcuts=Ctrl+3|1121|

    * create a `markdown.lua` file in the same folder where your
      `SciTEStartup.lua` file lives, and copy the following lua fragment:

            function Render()
              if editor.LexerLanguage == "markdown" then
                scite.MenuCommand(tonumber(props["markdown.rendering.command"]))
              end
            end

            function OnSavePointReached()
              pcall(Render)
              return false
            end

    * add the following line to your `SciTEStartup.lua` file:

            require "markdown"


## Workflow

* Open an exisiting markdown file or begin with an empty, _UTF-8 with BOM_ 
  encoded file and write some markup text;

* to start the preview, press F7: your default browser should open the temporary 
  html preview file;

* to refresh the preview, either:

* save the markdown file in SciTE, then refresh the preview in the browser;

* install an extension to let Firefox reload the modified file automatically
  --- I currently use the [Auto 
  Reload](https://addons.mozilla.org/en-US/firefox/addon/auto-reload) extension, 
  which monitors my `$(SciteUserHome)\.md` folder and reloads any file as it 
  changes.


## Notes

1) being a lua newby, the `pcall(Render)` call catches the _Editor pane is not
   accessible at this time_ error that occours at SciTE startup;

2) could not find a better method than 
   `scite.MenuCommand(tonumber(props["markdown.rendering.command"]))` to fire
   the markdown rendering procedure.
