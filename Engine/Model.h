#ifndef _TRILLEK_MODEL_H_
#define _TRILLEK_MODEL_H_

#include "Common.h"
#include "Mesh.h"

class Model
{
public:
    Model();

    bool loadFromFile(std::string fileName);

    void setPosition(float x, float y, float z);
    void setPosition(glm::vec3 pos);
    glm::vec3 getPosition() const;

    void setOrientation(float w, float x, float y, float z);
    void setOrientation(glm::quat ori);
    glm::quat getOrientation() const;

    void setScale(float xScale, float yScale, float zScale);
    void setScale(glm::vec3 scale);
    void setScale(float scale);

    glm::mat4 getModelMatrix();

    void render();

private:
    Mesh mesh;

    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 scale;

    bool outdated;
    glm::mat4 modelMatrix;
};

#endif