#include "engine.h"
#include <stdio.h>

Engine::Engine()
{
    this->window = nullptr;
    this->renderer = nullptr;
    this->configParser = nullptr;
    this->shaderManager = nullptr;
    this->logSys = nullptr;
    this->width = 0;
    this->height = 0;
}

bool Engine::init()
{
    // set up our engine subsystem
    if(!this->initSubsystem())
    {
        printf("Failed to initialize engine subsystems\n");
        return false;
    }

    // start up engine component services
    if(!this->initServices())
    {
        printf("Failed to initialize engine services\n");
        return false;
    }

    // load our configuration settings
    if(!this->configParser->loadConfigFile("C:\\Users\\Keivn\\Documents\\GitHub\\TrillekPrototype\\Debug\\settings.ini"))
    {
        this->logSys->error("Failed to initialize log parser");
        return false;
    }

    // create our window
    if(!this->initWindow())
    {
        this->logSys->error("Failed to initialize main window");
        return false;
    }

    // setup our graphics system
    if(!this->initGraphics())
    {
        this->logSys->error("Failed to initialize graphics subsystem");
        return false;
    }

    this->logSys->debug("Engine statup complete");

    return true;
}

void Engine::run()
{
    bool running = true;
    SDL_Event event;

    this->logSys->debug("Entering main engine loop");

    // main game loop
    while(running) 
    {
        // poll subsystem for events
        if(SDL_PollEvent(&event)) 
        {
            switch(event.type) 
            {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        // draw next frame
        this->renderer->update();
    }  
}

void Engine::shutdown()
{
    // shutdown the renderer
    this->renderer->shutdown();

    // delete our window
    SDL_DestroyWindow(this->window);

    // shutdown engine subsystems
    SDL_Quit();
}


bool Engine::initWindow()
{

    // get our height and width from the config file
    if(this->configParser->hasSetting(CONFIG_RESOLUTION_WIDTH) &&
        this->configParser->hasSetting(CONFIG_RESOLUTION_HEIGHT))
    {
        this->width = atoi(this->configParser->getSetting(CONFIG_RESOLUTION_WIDTH).c_str());
        this->height = atoi(this->configParser->getSetting(CONFIG_RESOLUTION_HEIGHT).c_str());
    }
    else
    {
        // fall back on default values
        this->width = 640;
        this->height = 800;
    }

    // create our window
    window = SDL_CreateWindow("Trillek Prototype", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!window)
    {
        this->logSys->error("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool Engine::initSubsystem()
{
    // initialize video and audio
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        this->logSys->error("Failed to initialize SDL subsystem: %s", SDL_GetError());
        return false;
    }

    // set our required attributes
    // NOTE: this MUST be after a successful SDL_Init
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return true;
}

bool Engine::initGraphics()
{
    // default to off
    bool vsync = false;

    // get any configuration settings we are interested in
    if(this->configParser->hasSetting(CONFIG_VSYNC))
        vsync = atoi(this->configParser->getSetting(CONFIG_VSYNC).c_str()) > 0;

    // initialize our renderer
    this->renderer = std::unique_ptr<RenderDevice>(new RenderDevice(*this->logSys));
    if(!this->renderer->init(vsync, this->width, this->height, this->window))
    {
        this->logSys->error("Failed to initialize renderer\n");
        return false;
    }

    return true;
}

bool Engine::initServices()
{
    // create our logger
    this->logSys = std::unique_ptr<LogSystem>(new LogSystem("trillek-engine.log"));
    if(!this->logSys->init())
    {
        printf("Failed to initialize log system\n");
        return false;
    }

    // create our configuration file parser
    this->configParser = std::unique_ptr<ConfigParser>(new ConfigParser(*this->logSys));

    return true;
}