/*
 * File  : AppPaths.h
 * Author: Mark Documento
 */

#ifndef _Croon_AppPaths_h_
#define _Croon_AppPaths_h_

struct AppPaths {
    static String DataDirectory();
    static Vector<String> FindFiles(String dir, String pattern);
};

#endif
