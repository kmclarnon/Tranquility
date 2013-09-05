#include "SceneManager.h"

SceneManager::SceneManager(const LogSystem &log, const ConfigParser &config, const InputManager &input) 
    : logSys(log), config(config), scene(log, config), input(input)
{

}

bool SceneManager::init()
{
    int width = this->config.getWindowWidth();
    int height = this->config.getWindowHeight();
    std::string modelDir = this->config.getModelDir();
    return this->scene.init(width, height, modelDir + "cube.obj");
}

bool SceneManager::update()
{
    return this->scene.update();
}

Scene& SceneManager::getActiveScene()
{
    return this->scene;
}