/*
 * File  : ConfigService.h
 * Author: Mark Documento
 */

#ifndef _Croon_ConfigService_h_
#define _Croon_ConfigService_h_

class ConfigService {
public:
    ~ConfigService();
    static String Get(const String& key, const String& defaultValue=String::GetVoid());
    static ConfigService& Set(const String& key, String value);
    static int GetInt(const String& key, int defaultValue=0);
    static ConfigService& Set(const String& key, int value);
    static void Serialize();
    static int GetFontSize();

public:
    static const int DefaultFontSize;
    static const int MinFontSize;
    static const int MaxFontSize;

private:
    ConfigService(const char* fname);
    
private:
    static ConfigService service;
    String fname;
};

#endif
