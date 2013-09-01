#ifndef _TRILLEK_SCENE_H_
#define _TRILLEK_SCENE_H_

#include "Common.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
    Scene();

    bool init(int width, int height);
    bool update();


    Light& getLight();
    Camera& getCamera();
    Mesh& getMesh();

private:
    Mesh mesh;
    Light light;
    Camera camera;
};

#endif