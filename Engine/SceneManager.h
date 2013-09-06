#ifndef _TRANQUILITYSCENE_MANAGER_H_
#define _TRANQUILITYSCENE_MANAGER_H_

#include "Common.h"
#include "LogSystem.h"
#include "ConfigParser.h"
#include "Scene.h"
#include "InputManager.h"
#include "SceneBuilder.h"

class SceneManager
{
public:
    SceneManager(const LogSystem &log, const ConfigParser &config, const InputManager &input);

    bool init();
    bool update();
    int addScene(std::string filename);
    bool setActiveScene(int id);
    const Scene& getActiveScene() const;

private:
    std::map<int, std::unique_ptr<Scene>> sceneMap;
    int idIndex;
    int idActive;

    std::unique_ptr<SceneBuilder> sceneBuilder;

    // we do not own this
    const LogSystem &logSys;
    const ConfigParser &config;
    const InputManager &input;

};

#endif