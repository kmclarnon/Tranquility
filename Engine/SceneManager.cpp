#include "SceneManager.h"

SceneManager::SceneManager(LogSystem &log, int width, int height) : logSys(log), width(width), height(height)
{

}

bool SceneManager::init()
{
    return this->scene.init(this->width, this->height);
}

bool SceneManager::update()
{
    return this->scene.update();
}

Scene& SceneManager::getActiveScene()
{
    return this->scene;
}