#ifndef _TRANQUILITYSCENE_H_
#define _TRANQUILITYSCENE_H_

#include "Common.h"
#include "LogSystem.h"
#include "ConfigParser.h"
#include "InputManager.h"
#include "Model.h"
#include "FPSCamera.h"
#include "Light.h"

class Scene
{
public:
    Scene(const LogSystem& log, const ConfigParser &config, const InputManager &input);

    bool init(int width, int height, std::string &model);
    bool update(double frameTime);

    const Light& getLight() const;
    const Camera& getCamera() const;
    const Model& getModel() const;

private:
    Model model;
    Light light;
    FPSCamera camera;

    // we don't own these
    const LogSystem &logSys;
    const ConfigParser &config;
    const InputManager &input;
};

#endif