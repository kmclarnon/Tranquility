#ifndef _TRILLEK_SCENE_H_
#define _TRILLEK_SCENE_H_

#include "Common.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
    Scene();

    bool init(int width, int height);
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