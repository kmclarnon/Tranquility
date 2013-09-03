#ifndef _TRILLEK_ENGINE_H_
#define _TRILLEK_ENGINE_H_

#include "Common.h"
#include "ConfigParser.h"
#include "RenderDevice.h"
#include "Shader.h"
#include "LogSystem.h"
#include "SceneManager.h"
#include "Timer.h"

class Engine
{
public:
    Engine();

    bool init();
    void run();
    void shutdown();

private:
    bool initGraphics();
    bool initGraphicsSubsystem();
    bool initWindow();
    bool initServices();

private:
    std::unique_ptr<RenderDevice> renderer;
    SDL_Window *window;
    std::unique_ptr<Shader> shaderManager;

    // Services
    std::unique_ptr<LogSystem> logSys;
    std::unique_ptr<ConfigParser> configParser;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<Timer> timer;
};

#endif