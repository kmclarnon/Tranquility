#include "SceneManager.h"

SceneManager::SceneManager(const LogSystem &log, const ConfigParser &config, const InputManager &input) 
    : logSys(log), config(config), input(input), idActive(0), idIndex(0)
{

}

bool SceneManager::init()
{
    int width = this->config.getWindowWidth();
    int height = this->config.getWindowHeight();
    std::string modelDir = this->config.getModelDir();

    this->sceneBuilder = std::unique_ptr<SceneBuilder>(new SceneBuilder(this->logSys, this->config, this->input));

    std::unique_ptr<Scene> tempScene = this->sceneBuilder->createScene("test dir");
    if(!tempScene)
        return false;

    tempScene->init(width, height, modelDir + "Mine/room.3ds");

    this->sceneMap.insert(std::pair<int, std::unique_ptr<Scene>>(this->idIndex, std::move(tempScene)));
    idIndex++;

    return true;
}

bool SceneManager::update(double frameTime)
{
    auto it = this->sceneMap.find(this->idActive);
    if(it == this->sceneMap.end())
        return false;

    return it->second->update(frameTime);
}

int SceneManager::addScene(std::string filename)
{
    std::unique_ptr<Scene> tempScene = this->sceneBuilder->createScene(filename);
    if(!tempScene)
        return false;

    this->sceneMap.insert(std::pair<int, std::unique_ptr<Scene>>(this->idIndex, std::move(tempScene)));
    return idIndex++;
}

bool SceneManager::setActiveScene(int id)
{
    auto it = this->sceneMap.find(id);
    if(it == this->sceneMap.end())
        return false;

    this->idActive = id;
    return true;
}

const Scene& SceneManager::getActiveScene() const
{
    auto it = this->sceneMap.find(this->idActive);
    assert(it != this->sceneMap.end());

    return *(it->second);
}
