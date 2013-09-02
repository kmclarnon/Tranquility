#include "Model.h"

Model::Model() : outdated(false) 
{

}

bool Model::loadFromFile(const std::string &fileName)
{
    return this->mesh.loadMesh(fileName);
}

void Model::update()
{
    // check if any changes have been made that would affect our model matrix
    if(this->outdated)
    {
        // calculate our rotation
        glm::mat4 rotation = glm::toMat4(this->orientation);
        // calculate model translation
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
        // calculate our model scale matrix
        glm::mat4 scale = glm::scale(this->scale);
        // apply rotation, then translation, and finally scale
        this->modelMatrix = scale * translation * rotation;
    }
}

void Model::setPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->outdated = true;
}

void Model::setPosition(const glm::vec3 &pos)
{
    this->position = pos;
    this->outdated = true;
}
glm::vec3 Model::getPosition() const
{
    return this->position;
}

void Model::setOrientation(float w, float x, float y, float z)
{
    this->orientation = glm::quat(w, x, y, z);
    this->outdated = true;
}
void Model::setOrientation(const glm::quat &ori)
{
    this->orientation = ori;
    this->outdated = true;
}
glm::quat Model::getOrientation() const
{
    return this->orientation;
}

void Model::setScale(float xScale, float yScale, float zScale)
{
    this->scale = glm::vec3(xScale, yScale, zScale);
    this->outdated = true;
}

void Model::setScale(const glm::vec3 &scale)
{
    this->scale = scale;
    this->outdated = true;
}

void Model::setScale(float scale)
{
    this->scale = glm::vec3(scale, scale, scale);
    this->outdated = true;
}

const glm::mat4& Model::getModelMatrix() const
{
    return this->modelMatrix;
}

void Model::render() const
{
    this->mesh.render();
}