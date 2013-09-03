#ifndef _TRILLEK_CONFIG_PARSER_H_
#define _TRILLEK_CONFIG_PARSER_H_

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
    std::string getModelPath();
    std::string getShaderPath();
    std::string getLogDir();

private:
    bool parseLine(std::string &line);
    bool parseWindowLine(std::string &line);
    bool parseGraphicsLine(std::string &line);
    bool parseAssetLine(std::string &line);
    bool parseLoggingLine(std::string &line);

    // Helpers
    bool parseBool(std::string &line);
    void loadDefaults();

private:
    ConfigGroups currentGroup;

    // config options
    int windowHeight, windowWidth, openGLMajor, openGLMinor;
    std::string windowName, shaderPath, modelPath, logDir;
    bool vsync;
};

#endif