#include "Camera.h"

const glm::vec3 Camera::FORWARD_VECTOR(0.0f,0.0f,-1.0f);
const glm::vec3 Camera::UP_VECTOR(0.0f,1.0f,.0f);
const glm::vec3 Camera::RIGHT_VECTOR(glm::cross(FORWARD_VECTOR, UP_VECTOR));

Camera::Camera()
{

}

void Camera::setView(float fov, int width, int height, float zNear, float zFar)
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->orientation = glm::quat(0.0f, 0.0f, 1.0f, 0.0f);
    this->projectionMatrix = glm::perspective(fov, (float)width / (float)height, zNear, zFar);
}

void Camera::update()
{
    // normalize our orientation
    glm::normalize(this->orientation);
    
    // calculate our new up and forward vectors
    this->up = Camera::UP_VECTOR * this->orientation;
    this->forward = this->position + (Camera::FORWARD_VECTOR * orientation);

    // calculte our new view matrix
    this->viewMat = glm::lookAt(this->position, this->forward, this->up); 
}

glm::mat4 Camera::getViewMatrix() const
{
    return this->viewMat;
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return this->projectionMatrix;
}

void Camera::setPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Camera::move(float right, float up, float forward)
{
    this->position += (Camera::FORWARD_VECTOR * forward) * this->orientation;
    this->position += (Camera::UP_VECTOR * up) * this->orientation;
    this->position += (Camera::RIGHT_VECTOR * right) * this->orientation;
}

void Camera::move(glm::vec3 trans)
{
    this->move(trans.x, trans.y, trans.z);
}

void Camera::rotate(float x, float y, float z)
{
    glm::quat qX = glm::angleAxis(x, 1.0f,0.0f,0.0f);
    glm::quat qY = glm::angleAxis(y, 0.0f,1.0f,0.0f);
    glm::quat qZ = glm::angleAxis(z, 0.0f,0.0f,1.0f); // TODO: Fix roll rotation.
    glm::quat change = qX * qY * qZ;
    this->orientation = change * this->orientation;
}

void Camera::rotate(glm::vec3 rot)
{
    this->rotate(rot.x, rot.y, rot.z);
}
