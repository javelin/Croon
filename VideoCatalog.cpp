/*
 * File  : VideoCatalog.cpp
 * Author: Mark Documento
 */

#include <Core/Core.h>

using namespace Upp;

#include "AppPaths.h"
#include "VideoCatalog.h"

Vector<String> VideoCatalog::FindVideoFiles(String videoDir) {
    return AppPaths::FindFiles(videoDir, "*.mp4");
}

String VideoCatalog::ThumbnailPath(String videoPath) {
    String tnPath = AppendFileName(AppPaths::DataDirectory(), GetFileName(videoPath));
    tnPath.Replace(".mp4", ".thumbnail.png");
    return tnPath;
}
