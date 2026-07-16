/*
 * File  : LrcPreviewGenerator.cpp
 * Author: Mark Documento
 */

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include "KarData.h"
#include "LrcGenerator.h"
#include "RichTextBuilder.h"
#include "LrcPreviewGenerator.h"

namespace {

String LrcPreviewStyle(const String& text) {
    if (text.StartsWith("("))
        return "/*@(11.218.81)";
    if (text.StartsWith("[1]: "))
        return "*@(255.0.0)";
    if (text.StartsWith("[2]: "))
        return "*@(0.0.255)";
    if (text.StartsWith("[B]: "))
        return "*@(255.0.255)";
    return "*@(0.0.0)";
}

}

String LrcPreviewGenerator::ToQtf(const KarData& data) {
    RTHelper rth;
    Vector<String> lines = Split(LrcGenerator::ToLrc(data), '\n');
    for (const auto& line : lines) {
        int endTimestamp = line.Find(']');
        if (line.StartsWith("[") && endTimestamp > 0) {
            String timestamp = line.Mid(0, endTimestamp + 1);
            String text = line.Mid(endTimestamp + 1);
            rth.Fmt("@(96.96.96)").Text(timestamp).EFmt()
               .Fmt(LrcPreviewStyle(text)).Text(text).EFmt()
               .NL();
        }
        else {
            rth.Fmt("*@(0.0.0)").Text(line).EFmt().NL();
        }
    }
    return rth.ToString();
}
