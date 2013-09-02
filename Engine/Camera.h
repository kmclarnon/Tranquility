#ifndef _TRILLEK_CAMERA_H_
#define _TRILLEK_CAMERA_H_

#include "Common.h"

class Camera
{
public:
    Camera();

    void update();
    void setView(float fov, int width, int height, float zNear, float zFar);
    void setPosition(float x, float y, float z);
    void move(float right, float up, float forward);
    void rotate(float x, float y, float z);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    void move(glm::vec3 trans);
    void rotate(glm::vec3 rot);

private:
    glm::mat4 viewMat;
    glm::mat4 projectionMatrix;
    glm::vec3 position;
    glm::quat orientation;

    const static glm::vec3 FORWARD_VECTOR;
    const static glm::vec3 UP_VECTOR;
    const static glm::vec3 RIGHT_VECTOR;

};

#endif