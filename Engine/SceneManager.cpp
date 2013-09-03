#include "SceneManager.h"

SceneManager::SceneManager(LogSystem &log, int width, int height, const std::string &modelDir) : logSys(log), width(width), height(height), modelDir(modelDir)
{

}

bool SceneManager::init()
{
    return this->scene.init(this->width, this->height, this->modelDir + "cube.obj");
}

bool SceneManager::update()
{
    return this->scene.update();
}

Scene& SceneManager::getActiveScene()
{
    return this->scene;
}