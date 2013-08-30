#ifndef _TRILLEK_ENGINE_H_
#define _TRILLEK_ENGINE_H_

#include "Common.h"
#include "ConfigParser.h"
#include "RenderDevice.h"
#include "Shader.h"
#include "AssetImporter.h"
#include "LogSystem.h"

class Engine
{
public:
    Engine();

    bool init();
    void run();
    void shutdown();

private:
    bool initGraphics();
    bool initSubsystem();
    bool initWindow();
    bool initServices();

private:
    std::unique_ptr<RenderDevice> renderer;
    SDL_Window *window;
    std::unique_ptr<Shader> shaderManager;
    int width, height;

    // Services
    std::unique_ptr<LogSystem> logSys;
    std::unique_ptr<AssetImporter> assetImporter;
    std::unique_ptr<ConfigParser> configParser;
};

#endif