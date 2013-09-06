#ifndef _TRANQUILITY_SCENE_BUILDER_H_
#define _TRANQUILITY_SCENE_BUILDER_H_

#include "Common.h"
#include "LogSystem.h"
#include "ConfigParser.h"
#include "InputManager.h"
#include "Scene.h"

class SceneBuilder
{
public:
    SceneBuilder(const LogSystem &log, const ConfigParser &config, const InputManager &input);

    std::unique_ptr<Scene> createScene(std::string filename);

private:

    // we don't own these
    const LogSystem &logSys;
    const ConfigParser &config;
    const InputManager &input;
};

#endif