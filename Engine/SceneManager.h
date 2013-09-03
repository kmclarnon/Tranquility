#ifndef _TRANQUILITYSCENE_MANAGER_H_
#define _TRANQUILITYSCENE_MANAGER_H_

#include "Common.h"
#include "LogSystem.h"
#include "Scene.h"

class SceneManager
{
public:
    SceneManager(LogSystem &log, int width, int height, const std::string &modelDir);

    bool init();
    bool update();

    Scene& getActiveScene();

private:
    Scene scene;
    int width, height;
    const std::string &modelDir;

    // we do not own this
    const LogSystem &logSys;

};

#endif