#ifndef _TRANQUILITYSCENE_MANAGER_H_
#define _TRANQUILITYSCENE_MANAGER_H_

#include "Common.h"
#include "LogSystem.h"
#include "ConfigParser.h"
#include "Scene.h"
#include "InputManager.h"

class SceneManager
{
public:
    SceneManager(const LogSystem &log, const ConfigParser &config, const InputManager &input);

    bool init();
    bool update();

    Scene& getActiveScene();

private:
    Scene scene;

    // we do not own this
    const LogSystem &logSys;
    const ConfigParser &config;
    const InputManager &input;

};

#endif