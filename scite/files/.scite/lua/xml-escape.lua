-- order matters!
local escapingDict = {
    { ["&" ] = "&amp;"  },
    { ["<" ] = "&lt;"   },
    { [">" ] = "&gt;"   },
    { ["\""] = "&quot;" },
    { ["'" ] = "&apos;" }
}

-- order matters!
local unescapingDict = {
    { ["&apos;"] = "'"  },
    { ["&quot;"] = "\"" },
    { ["&gt;"  ] = ">"  },
    { ["&lt;"  ] = "<"  },
    { ["&amp;" ] = "&"  }
}

function Replace(text, dict)
    for pos, replacement in pairs(dict) do
        for old, new in pairs(replacement) do
            text = string.gsub(text, old, new)
        end
    end
    return text
end

function XmlEscapeSelection()
    editor:ReplaceSel(Replace(editor:GetSelText(), escapingDict))
end

function XmlUnescapeSelection()
    editor:ReplaceSel(Replace(editor:GetSelText(), unescapingDict))
end
