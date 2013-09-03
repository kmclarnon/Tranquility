#ifndef _TRANQUILITYGLDEVICE_H_
#define _TRANQUILITYGLDEVICE_H_

#include "Common.h"
#include "Mesh.h"
#include "LogSystem.h"

class GLDevice
{
public:
    GLDevice(const LogSystem &logSys, SDL_Window *window);
    bool init(bool vsync);
    void shutdown();

    void resize(int width, int height);

    void beginScene(float r, float g, float b, float a);
    void endScene();

private:
    SDL_GLContext context;

    // we do not own this
    SDL_Window *window;
    const LogSystem &logSys;
};

#endif