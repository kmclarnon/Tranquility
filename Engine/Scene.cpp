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
    static float rotation = 0.0f;
    static float scale = 1.0f;

    // update the camera
    this->camera.update();

    // Update the rotation variable each frame.
    rotation += 0.0174532925f * 1.0f;
    if(rotation > 360.0f)
    {
        rotation -= 360.0f;
    }

    scale -= 0.001;
    if(scale < 0.5f)
    {
        scale = 1.0f;
    }

    this->model.setOrientation(glm::quat(glm::vec3(rotation, rotation, 0.0f)));
    this->model.setScale(scale);

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