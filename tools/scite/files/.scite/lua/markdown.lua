function Render()
    if editor.LexerLanguage == "markdown" then
        scite.MenuCommand(tonumber(props["markdown.rendering.command"]))
    end
end

function OnSavePointReached()
    pcall(Render)
    return false
end
