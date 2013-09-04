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

    int getWindowWidth() const;
    int getWindowHeight() const;
    int getGLMajorVer() const;
    int getGLMinorVer() const;
    const std::string& getWindowName() const;
    bool getVsync() const;
    const std::string& getModelDir() const;
    const std::string& getShaderDir() const;
    const std::string& getLogDir() const;
    const std::string& getResourceDir() const;
    const std::string& getFallbackTexture() const;

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
    std::string windowName, shaderDir, modelDir, resourceDir, logDir, fallbackTexture;
    bool vsync;
};

#endif