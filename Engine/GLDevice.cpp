#include "gldevice.h"

GLDevice::GLDevice(LogSystem &logSys, SDL_Window *window) : logSys(logSys)
{
    this->context = nullptr;
    this->window = window;
}

bool GLDevice::init(bool vsync)
{
    this->context = SDL_GL_CreateContext(this->window);
    if(!this->context)
    {
        printf("Failed to initialize GLDevice\n");
        return false;
    }

    if(vsync)
    {
        // Set swap interval to late swap tearing (best of both worlds)
        if(SDL_GL_SetSwapInterval(-1) < 0)
        {
            // System doesn't support late swap tearing, fallback on vsync
            if(SDL_GL_SetSwapInterval(1) < 0)
            {
                printf("Failed to enable vsync: %s\n", SDL_GetError());
                return false;
            }
        }
    }
    else
    {
        if(SDL_GL_SetSwapInterval(0) < 0)
        {
            printf("Failed to enable vsync: %s\n", SDL_GetError());
            return false;
        }
    }

    // need to set this global switch for glew to properly get 3.2+ profile functions
    glewExperimental = TRUE;
    // Load our OpenGL extensions
    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        printf("Error loading openGL extensions: %s\n", glewGetErrorString(err));
        return false;
    }

    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Render: %s\n", glGetString(GL_RENDERER));

    // debug print openGL versions
    int glVersion[2] = { -1, -1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    printf("Context: OpenGL %i.%i\n", glVersion[0], glVersion[1]);

    // enable some basic rendering options
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

void GLDevice::shutdown()
{
    SDL_GL_DeleteContext(this->context);
    this->window = nullptr;
}

void GLDevice::resize(int width, int height)
{

}

void GLDevice::beginScene(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLDevice::endScene()
{
    SDL_GL_SwapWindow(this->window);
}