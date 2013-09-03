#ifndef _TRANQUILITYSCENE_H_
#define _TRANQUILITYSCENE_H_

#include "Common.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
    Scene();

    bool init(int width, int height, std::string &model);
    bool update();

    const Light& getLight() const;
    const Camera& getCamera() const;
    const Model& getModel() const;

private:
    Model model;
    Light light;
    Camera camera;
};

#endif