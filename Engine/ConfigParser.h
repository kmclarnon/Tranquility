#ifndef _TRILLEK_CONFIG_PARSER_H_
#define _TRILLEK_CONFIG_PARSER_H_

#include "Common.h"
#include "StringUtils.h"
#include "ConfigOptions.h"
#include "ConfigItem.h"
#include "LogSystem.h"
#include "tinyxml2.h"

class ConfigParser
{
public:
    ConfigParser(const LogSystem &logSys);

    bool loadConfig(std::string file);
    ConfigItem getSetting(std::string name);

private:
    bool loadConfigFile(std::string file);

    typedef std::map<std::string, ConfigItem> ConfigMap;
    std::unique_ptr<ConfigMap> settings;

    // We do not own this
    const LogSystem &logSys;
};

#endif