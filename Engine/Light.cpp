#include "Light.h"

Light::Light()
{
    this->lightDirection = glm::vec3();
    this->diffuseColor = glm::vec4();
    this->ambientLight = glm::vec4();
}

void Light::setLightDirection(float x, float y, float z)
{
    this->lightDirection = glm::vec3(x, y, z);
}

void Light::setDiffuseColor(float r, float g, float b, float a)
{
    this->diffuseColor = glm::vec4(r, g, b, a);
}

void Light::setAmbientLight(float r, float g, float b, float a)
{
    this->ambientLight = glm::vec4(r, g, b, a);
}

glm::vec3 Light::getLightDirection() const
{
    return this->lightDirection;
}

glm::vec4 Light::getDiffuseColor() const
{
    return this->diffuseColor;
}

glm::vec4 Light::getAmbientLight() const
{
    return this->ambientLight;
}
