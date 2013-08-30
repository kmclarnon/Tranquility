#ifndef _TRILLEK_GLDEVICE_H_
#define _TRILLEK_GLDEVICE_H_

#include "Common.h"
#include "Mesh.h"
#include "LogSystem.h"

class GLDevice
{
public:
    GLDevice(LogSystem &logSys, SDL_Window *window);
    bool init(bool vsync);
    void shutdown();

    void resize(int width, int height);

    void beginScene(float r, float g, float b, float a);
    void endScene();

private:
    bool loadExtensions();

private:
    SDL_GLContext context;

    // we do not own this
    SDL_Window *window;
    LogSystem logSys;
};

#endif