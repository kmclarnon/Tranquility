#ifndef _TRILLEK_RENDER_DEVICE_H_
#define _TRILLEK_RENDER_DEVICE_H_

#include "Common.h"
#include "GLDevice.h"
#include "Shader.h"
#include "LogSystem.h"
#include "Scene.h"
#include "SceneManager.h"


class RenderDevice
{
public:
    RenderDevice(const LogSystem &logSys, SceneManager &sceneManager, std::string shaderDir);

    bool init(bool vsync, int width, int height, SDL_Window *window);
    bool update();

private:
    SceneManager &sceneManager;
    std::unique_ptr<GLDevice> device;
    std::unique_ptr<Shader> shader;
    std::string shaderDir;

    // We do not own this
    const LogSystem &logSys;


    
};

#endif