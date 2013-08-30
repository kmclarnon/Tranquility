#ifndef _TRILLEK_RENDER_DEVICE_H_
#define _TRILLEK_RENDER_DEVICE_H_

#include "Common.h"
#include "GLDevice.h"
#include "Shader.h"
#include "LogSystem.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"


class RenderDevice
{
public:
    RenderDevice(LogSystem &logSys);

    bool init(bool vsync, int width, int height, SDL_Window *window);
    bool update();

    void shutdown();

private:

private:
    // test
    GLuint vbo, vao;
    Mesh mesh;
    Light light;

    // We do not own this
    LogSystem &logSys;

    GLDevice *device;
    Shader *shader;
    Camera *camera;
};

#endif