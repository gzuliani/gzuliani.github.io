function SplitLines(text)
    local lines = {}
    local function helper(line) table.insert(lines, line) return "" end
    helper((string.gsub(text, "(.-)\r?\n", helper)))
    return lines
end

function GetEol()
    if editor.EOLMode == SC_EOL_CRLF then
        return "\r\n"
    elseif editor.EOLMode == SC_EOL_CR then
        return "\r"
    elseif editor.EOLMode == SC_EOL_LF then
        return "\n"
    end
end

function GetWrapWidth()
    return tonumber(props["edge.column"])
end

function WrapText(text, width)
    local wrappedText = {}
    for i, line in pairs(SplitLines(text)) do
        wrappedLine = ""
        for token in string.gmatch(line, "[^%s]+") do
            if string.len(token .. wrappedLine) > width then
                wrappedText[#wrappedText + 1] = wrappedLine
                wrappedLine = token .. " "
            else
                wrappedLine = wrappedLine .. token .. " "
            end
        end
        wrappedText[#wrappedText + 1] = string.gsub(wrappedLine, "%s$", "")
    end
    return table.concat(wrappedText, GetEol())
end

function WrapSelText()
    local pos = editor.SelectionStart
    editor:ReplaceSel(WrapText(editor:GetSelText(), GetWrapWidth()))
    editor:GotoPos(pos)
end

function WrapAllText()
    editor:SetText(WrapText(editor:GetText(), GetWrapWidth()))
    editor:GotoPos(0)
end

function UnwrapText(text)
    local segments = {}
    local paragraphs = {}
    for i, line in pairs(SplitLines(text)) do
        if line == "" then
            paragraphs[#paragraphs + 1] = table.concat(segments, " ")
            if #segments > 0 then
                paragraphs[#paragraphs + 1] = ""
            end
            segments = {}
        else
            segments[#segments + 1] = line
        end
    end
    if #segments > 0 then
        paragraphs[#paragraphs + 1] = table.concat(segments, " ")
        segments = {}
    end
    return table.concat(paragraphs, GetEol())
end

function UnwrapSelText()
    local pos = editor.SelectionStart
    editor:ReplaceSel(UnwrapText(editor:GetSelText()))
    editor:GotoPos(pos)
end

function UnwrapAllText()
    editor:SetText(UnwrapText(editor:GetText()))
    editor:GotoPos(0)
end
