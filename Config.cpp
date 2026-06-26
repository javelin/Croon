/*
 * File  : Config.cpp
 * Author: Mark Documento
 */

#include "Croon.h"

Config Config::config;

const int Config::DefaultFontSize = ConfigService::DefaultFontSize;
const int Config::MinFontSize = ConfigService::MinFontSize;
const int Config::MaxFontSize = ConfigService::MaxFontSize;

Config::~Config() {
}
