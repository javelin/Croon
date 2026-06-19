/*
 * File  : Config.cpp
 * Author: Mark Documento
 */

#include "Croon.h"

#define CONFIG_FILE "config"

Config Config::config(AppendFileName(GetDataDirectory(), CONFIG_FILE));

const int Config::DefaultFontSize=72;
const int Config::MinFontSize=70;
const int Config::MaxFontSize=100;

Config::Config(const char* fname) : fname(fname) {
    RegisterGlobalConfig(FFMPEG_LOCATION);
    RegisterGlobalConfig(LYRICS_PREFIX);
    RegisterGlobalConfig(LYRICS_SUFFIX);
    RegisterGlobalConfig(FONT_SIZE);
    RegisterGlobalConfig(MUSIC_DIR);
    RegisterGlobalConfig(PROJECT_DIR);
    RegisterGlobalConfig(EXPORT_DIR);
    RegisterGlobalConfig(VIDEO_DIR);
    RegisterGlobalConfig(PROJECT_LIST);
    RegisterGlobalConfig(WIN_X);
    RegisterGlobalConfig(WIN_Y);
    RegisterGlobalConfig(WIN_W);
    RegisterGlobalConfig(WIN_H);
    FileIn f(fname);
    SerializeGlobalConfigs(f);
}

Config::~Config() {
    Serialize();
}

String Config::Get(const String& key, const String& defaultValue) {
    String value;
    return LoadFromGlobal(value, key) ? value : defaultValue;
}

Config& Config::Set(const String& key, String value) {
    StoreToGlobal(value, key);
    return config;
}

int Config::GetInt(const String& key, int defaultValue) {
    int value;
    return LoadFromGlobal(value, key) ? value : defaultValue;
}

Config& Config::Set(const String& key, int value) {
    StoreToGlobal(value, key);
    return config;
}

void Config::Serialize() {
    FileOut f(fname);
    SerializeGlobalConfigs(f);
}

int Config::GetFontSize() {
    return std::max(MinFontSize, std::min(MaxFontSize, GetInt(FONT_SIZE, DefaultFontSize)));
}