#ifndef _TRILLEK_SCENE_MANAGER_H_
#define _TRILLEK_SCENE_MANAGER_H_

#include "Common.h"
#include "LogSystem.h"
#include "Scene.h"

class SceneManager
{
public:
    SceneManager(LogSystem &log, int width, int height);

    bool init();
    bool update();

    Scene& getActiveScene();

private:
    Scene scene;
    int width, height;

    // we do not own this
    const LogSystem &logSys;

};

#endif