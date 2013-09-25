function AnsiToHex(text, format)
    return string.gsub(text, ".", function(c) return string.format(format, c:byte(1)) end)
end

function HexToAnsi(text)
    return string.gsub(text, "%x%x", function(c) return string.format("%c", tonumber(c, 16)) end)
end

function AnsiToHexSelection()
    editor:ReplaceSel(AnsiToHex(editor:GetSelText(), "%2x"))
end

function AnsiToCHexStringSelection()
    editor:ReplaceSel('"' .. AnsiToHex(editor:GetSelText(), "\\x%2x") .. '"')
end

function HexToAnsiSelection()
    editor:ReplaceSel(HexToAnsi(editor:GetSelText()))
end
