#ifndef _TRILLEK_RENDER_DEVICE_H_
#define _TRILLEK_RENDER_DEVICE_H_

#include "Common.h"
#include "GLDevice.h"
#include "Shader.h"
#include "LogSystem.h"
#include "Scene.h"


class RenderDevice
{
public:
    RenderDevice(const LogSystem &logSys);

    bool init(bool vsync, int width, int height, SDL_Window *window);
    bool update();

private:
    // test
    //Mesh mesh;
    //Light light;
    //Camera *camera;
    Scene scene;

    // We do not own this
    const LogSystem &logSys;

    std::unique_ptr<GLDevice> device;
    std::unique_ptr<Shader> shader;
    
};

#endif