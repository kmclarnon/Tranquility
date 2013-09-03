#ifndef _TRANQUILITY_CONFIG_PARSER_H_
#define _TRANQUILITY_CONFIG_PARSER_H_

#include "Common.h"
#include "ConfigOptions.h"
#include "LogSystem.h"
#include "StringUtils.h"

class ConfigParser
{
public:
    ConfigParser();

    void loadConfig(std::string configFile);

    int getWindowWidth();
    int getWindowHeight();
    int getGLMajorVer();
    int getGLMinorVer();
    std::string getWindowName();
    bool getVsync();
    std::string getModelDir();
    std::string getShaderDir();
    std::string getLogDir();
    std::string getResourceDir();

private:
    bool parseLine(std::string &line);
    bool parseWindowLine(std::string &line);
    bool parseGraphicsLine(std::string &line);
    bool parseResourceLine(std::string &line);
    bool parseLoggingLine(std::string &line);

    // Helpers
    bool parseBool(std::string &line);
    void loadDefaults();

private:
    ConfigGroups currentGroup;

    // config options
    int windowHeight, windowWidth, openGLMajor, openGLMinor;
    std::string windowName, shaderDir, modelDir, resourceDir, logDir;
    bool vsync;
};

#endif