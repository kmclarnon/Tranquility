#ifndef _TRILLEK_LIGHT_H_
#define _TRILLEK_LIGHT_H_

#include "Common.h"

class Light
{
public:
    Light();

    void setLightDirection(float x, float y, float z);
    void setDiffuseColor(float r, float g, float b, float a);
    void setAmbientLight(float r, float g, float b, float a);

    glm::vec3 getLightDirection();
    glm::vec4 getDiffuseColor();
    glm::vec4 getAmbientLight();

private:
    glm::vec3 lightDirection;
    glm::vec4 diffuseColor;
    glm::vec4 ambientLight;
};

#endif