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

    this->model.setScale(1.0f);

    return res;
}

bool Scene::update()
{
    static float rotation = 0.0f;

    rotation += 0.0174532925f * 1.0f;
    if(rotation > 360.0f)
    {
        rotation -= 360.0f;
    }

    // update the camera
    this->camera.update();

    this->model.setOrientation(glm::quat(glm::vec3(0.0f, rotation, 0.0f)));

    // update the model
    this->model.update();

    return true;
}

const Light& Scene::getLight() const
{
    return this->light;
}

const Camera& Scene::getCamera() const
{
    return this->camera;
}

const Model& Scene::getModel() const
{
    return this->model;
}