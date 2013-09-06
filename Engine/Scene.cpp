#include "Scene.h"

Scene::Scene(const LogSystem &log, const ConfigParser &config, const InputManager &input) 
    : logSys(log), config(config), model(log, config), input(input)
{

}

bool Scene::init(int width, int height, std::string &model)
{
    // set up our camera
    this->camera.setView(45.0f, width, height, 0.1f, 1000.0f);
    this->camera.setPosition(0.0f, 0.0f, 0.0f);

    // set up our light
    this->light.setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
    this->light.setLightDirection(1.0f, 0.0f, 0.0f);
    this->light.setAmbientLight(0.15f, 0.15f, 0.15f, 1.0f);

    // load our model
    if(!this->model.loadFromFile(model))
        return false;


    this->model.setScale(1.0f);
    this->model.setOrientation(glm::quat(glm::vec3((float)M_PI/2, 0.0f, 0.0f)));

    return true;
}

bool Scene::update()
{
    // update the camera
    this->camera.update();

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