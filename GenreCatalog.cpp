/*
 * File  : GenreCatalog.cpp
 * Author: Mark Documento
 */

#include <Core/Core.h>

using namespace Upp;

#include "GenreCatalog.h"

const Vector<String>& GenreCatalog::List() {
    static Vector<String> genre{
        "Ballad",
        "Blues",
        "Blues Rock",
        "Country",
        "Folk",
        "Heavy Metal",
        "Hip-Hop",
        "Pop Standard",
        "Power Ballad",
        "OPM",
        "Metal",
        "Pop",
        "R&B",
        "Rock",
        "Rock n Roll",
        "Soft Rock"
    };
    return genre;
}
