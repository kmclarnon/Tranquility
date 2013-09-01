#include "Scene.h"

Scene::Scene()
{

}

bool Scene::init(int width, int height)
{
    // set up our camera
    this->camera.setView(45.0f, width, height, 0.1f, 1000.0f);
    this->camera.setPosition(0.0f, 0.0f, -10.0f);

    // set up our light
    this->light.setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    this->light.setLightDirection(1.0f, 0.0f, 0.0f);
    this->light.setAmbientLight(0.15f, 0.15f, 0.15f, 1.0f);

    // load our model
    bool res = this->model.loadFromFile("Models/cube.obj");

    this->model.setScale(0.5);

    return res;
}

bool Scene::update()
{
    this->camera.update();

    return true;
}

Light& Scene::getLight()
{
    return this->light;
}

Camera& Scene::getCamera()
{
    return this->camera;
}

Model& Scene::getModel()
{
    return this->model;
}