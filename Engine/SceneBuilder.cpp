#include "SceneBuilder.h"

SceneBuilder::SceneBuilder(const LogSystem &log, const ConfigParser &config, const InputManager &input)
    : logSys(log), config(config), input(input)
{

}

std::unique_ptr<Scene> SceneBuilder::createScene(std::string filename)
{
    std::unique_ptr<Scene> s = std::unique_ptr<Scene>(new Scene(logSys, config, input));

    return s;

}