function OnSave()
    if editor.LexerLanguage == "markdown" then
        scite.MenuCommand(tonumber(props["markdown.rendering.command"]))
    end
end
