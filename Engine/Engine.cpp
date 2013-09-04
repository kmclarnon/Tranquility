#include "engine.h"
#include <stdio.h>

Engine::Engine()
{
}

bool Engine::init()
{
    // start up engine component services
    if(!this->initServices())
    {
        printf("Failed to initialize engine services\n");
        return false;
    }

    // set up our engine subsystem
    if(!this->initGraphicsSubsystem())
    {
        printf("Failed to initialize engine subsystems\n");
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

    this->logSys->debug("Engine startup complete");

    return true;
}

void Engine::run()
{
    bool running = true;
    SDL_Event event;
    double frameTime;

    this->logSys->debug("Entering main engine loop");

    // start up our timer
    this->timer->start();

    // main game loop
    while(running) 
    {
        // get our frame time
        frameTime = this->timer->getElapsedTimeInMilliSec();
        //this->logSys->debug("Elapsed time: %lf", frameTime);
        // start measuring our current frame
        this->timer->resetElapsed();

        // poll subsystem for events
        if(SDL_PollEvent(&event)) 
        {
            switch(event.type) 
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_EventType::SDL_KEYDOWN:
                case SDL_EventType::SDL_KEYUP:
                    //this->sceneManager->handleKeyboardEvent(event.key);
                    break;
                case SDL_EventType::SDL_MOUSEBUTTONDOWN:
                case SDL_EventType::SDL_MOUSEBUTTONUP:
                    //this->sceneManager->handleMouseEvent(event.button);
                    break;
                default:
                    break;
            }
        }

        // tell our scenes to update
        this->sceneManager->update();

        // draw next frame
        this->renderer->update();
    }  
}

void Engine::shutdown()
{
    // delete our window
    SDL_DestroyWindow(this->window);

    // shutdown engine subsystems
    SDL_Quit();
}


bool Engine::initWindow()
{
    std::string name = this->configParser->getWindowName();
    int width = this->configParser->getWindowWidth();
    int height = this->configParser->getWindowHeight();

    // create our window
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, width, height, 
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(!window)
    {
        this->logSys->error("Failed to create window: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool Engine::initGraphicsSubsystem()
{
    // initialize video and audio
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        this->logSys->error("Failed to initialize SDL subsystem: %s", SDL_GetError());
        return false;
    }

    // set our required attributes
    // NOTE: this MUST be after a successful SDL_Init
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->configParser->getGLMajorVer());
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->configParser->getGLMinorVer());
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return true;
}

bool Engine::initGraphics()
{
    // get any configuration settings we are interested in
    bool vsync = this->configParser->getVsync();
    std::string shaderDir = this->configParser->getShaderDir();
    std::string modelDir = this->configParser->getModelDir();
    int width = this->configParser->getWindowWidth();
    int height = this->configParser->getWindowHeight();

    // create our scene manager
    this->sceneManager = std::unique_ptr<SceneManager>(new SceneManager(*this->logSys, *this->configParser));

    // initialize our renderer
    this->renderer = std::unique_ptr<RenderDevice>(new RenderDevice(*this->logSys, *this->sceneManager, shaderDir));
    if(!this->renderer->init(vsync, width, height, this->window))
    {
        this->logSys->error("Failed to initialize renderer\n");
        return false;
    }

    // initialize our scene manager
    if(!this->sceneManager->init())
    {
        this->logSys->error("Failed to initialize scene manager");
        return false;
    }

    return true;
}

bool Engine::initServices()
{
    // create our configuration file parser
    this->configParser = std::unique_ptr<ConfigParser>(new ConfigParser());

    // load our configuration settings
    this->configParser->loadConfig(DEFAULT_CONFIG_FILE);

    // create our logger
    this->logSys = std::unique_ptr<LogSystem>(new LogSystem(this->configParser->getLogDir() + "engine.log"));
    if(!this->logSys->init())
    {
        printf("Failed to initialize log system\n");
        return false;
    }

    // create our timer
    this->timer = std::unique_ptr<Timer>(new Timer());

    return true;
}