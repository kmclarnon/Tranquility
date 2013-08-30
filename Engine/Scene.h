#ifndef _TRILLEK_SCENE_H_
#define _TRILLEK_SCENE_H_

#include "Common.h"
#include "Mesh.h"

class Scene
{
public:
    Scene();

    void addMesh(Mesh &m);
};

#endif