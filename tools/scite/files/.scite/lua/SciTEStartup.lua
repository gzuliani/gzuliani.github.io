function HexToDec(s)
    return tonumber(s, 16)
end

function RGBToNum(r, g, b)
    return r + 256 * g + 65536 * b
end

function OnClear()
    local value = props["colour.calltiphlt.fore"]
    if value ~= "" then
        local s,e,r,g,b=string.find(value, "^#(%x%x)(%x%x)(%x%x)$")
        scite.SendEditor(SCI_CALLTIPSETFOREHLT, RGBToNum(HexToDec(r), HexToDec(g), HexToDec(b)))
    end
end

function RemoveEmptyLines()
    local text = editor:GetText()
    if #text == 0 then return end
    local textChanged, count = false
    while true do
        text, count = string.gsub(text, "(\r?\n)%s*\r?\n", "%1")
        if count == 0 then break end
        textChanged = true
    end
    if textChanged then
        editor:SetText(text)
        editor:GotoPos(0)
    end
end

package.path = package.path..";"..props["SciteUserHome"].."/.scite/lua/?.lua"
require "snippets"
require "ansi"
require "javadoc"
require "markdown"
require "wrap"
require "xml"
