#include "Model.h"

Model::Model() : position(0.0f, 0.0f, 0.0f), outdated(false) 
{

}

bool Model::loadFromFile(std::string fileName)
{
    return this->mesh.loadMesh(fileName);
}

void Model::setPosition(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->outdated = true;
}

void Model::setPosition(glm::vec3 pos)
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
void Model::setOrientation(glm::quat ori)
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

void Model::setScale(glm::vec3 scale)
{
    this->scale = scale;
    this->outdated = true;
}

void Model::setScale(float scale)
{
    this->scale = glm::vec3(scale, scale, scale);
    this->outdated = true;
}

glm::mat4 Model::getModelMatrix()
{
    if(this->outdated)
    {
        glm::mat4 rotation = glm::toMat4(this->orientation);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
        this->modelMatrix = glm::scale(this->scale) * translation * rotation;
    }

    return this->modelMatrix;
}

void Model::render()
{
    this->mesh.render();
}