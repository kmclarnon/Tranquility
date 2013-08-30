#ifndef _TRILLEK_CONFIG_PARSER_H_
#define _TRILLEK_CONFIG_PARSER_H_

#include "common.h"
#include "stringutils.h"
#include "configoptions.h"
#include "LogSystem.h"

class ConfigParser
{
public:
    ConfigParser(LogSystem &logSys);

    bool loadConfigFile(std::string file);

    bool hasSetting(std::string name);
    std::string getSetting(std::string name);

    std::pair<int, int> parseResolution(std::string res);

private:
    std::map<std::string, std::string> *settings;

    // We do not own this
    LogSystem &logSys;
};

#endif