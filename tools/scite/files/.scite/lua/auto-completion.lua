local eolVariants = {
    [SC_EOL_CRLF] = "\r\n",
    [SC_EOL_CR] = "\r",
    [SC_EOL_LF] = "\n"

    }

-- autocompletion
function OnChar(ch)
    --
    -- brackets
    --
--~     if ch == "(" then
--~         editor:InsertText(-1, ")")
--~     end

--~     if ch == "[" then
--~         editor:InsertText(-1, "]")
--~     end

--~     if ch == "{" then
--~         editor:InsertText(-1, "}")
--~     end

    --
    -- quotes
    --
--~     if ch == "\"" then
--~         editor:InsertText(-1, "\"")
--~     end
--~     if ch == "\'" then
--~         editor:InsertText(-1, "\'")
--~     end

    --
    -- javadoc
    --
    -- requires: indent.maintain.$(file.patterns.cpp)=0
    if ch == "\n" and editor.LexerLanguage == "cpp" then

        local mark = "/**"
        local markLen = string.len(mark)

        local eol = eolVariants[editor.EOLMode]
        local eolLen = string.len(eol)
        local eolPos = editor.CurrentPos - eolLen

        local prevLineNum = editor:LineFromPosition(eolPos)
        local prevLine = editor:GetLine(prevLineNum)

        if string.match(prevLine, "^%s*/%*%*") then
            local indentation = string.match(prevLine, "^(%s*)")

            local textToInsert = indentation.." * "
            local caretFinalPos = editor.CurrentPos + string.len(textToInsert)

            -- check whether this is the beginning of a new comment
            -- (it is iff the following line starts with a "*");
            -- if so, add a new line with a properly indented end-of-comment mark
            local nextLine = editor:GetLine(prevLineNum + 2)

            editor:InsertText(-1, textToInsert)

            if nextLine == nil or string.find(nextLine, "^%s*%*") == nil then
                editor:GotoPos(editor.LineEndPosition[prevLineNum + 1])
                editor:InsertText(-1, eol..indentation.." */")
            end

            editor:GotoPos(caretFinalPos)
        else
            -- check whether we're in the middle of a comment
            -- (we are iff the previous lines begin with "*" or "/**")
            local i = prevLineNum

            while i >= 0 do
                local line = editor:GetLine(i)
                i = i - 1

                -- reached the beginning of the comment
                local start_, end_, indentation = string.find(line, "^(%s*)/%*%*")
                if indentation then
                    local textToInsert = indentation.." * "
                    local caretPos = editor.CurrentPos + string.len(textToInsert)
                    editor:InsertText(-1, textToInsert)
                    editor:GotoPos(caretPos)
                    break
                end

                -- don't expand the comment when on the last line (i.e. near "*/")
                if string.find(line, "^%s*%*/") ~= nil then
                    break
                end

                -- not a comment, exit immediately
                if string.find (line, "^%s*%*") == nil then
                    break
                end
            end
        end
    end
    return false
end
