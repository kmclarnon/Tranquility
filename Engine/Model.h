#ifndef _TRILLEK_MODEL_H_
#define _TRILLEK_MODEL_H_

#include "Common.h"
#include "Mesh.h"

class Model
{
public:
    Model();

    bool loadFromFile(const std::string &fileName);

    void update();

    void setPosition(float x, float y, float z);
    void setPosition(const glm::vec3 &pos);
    glm::vec3 getPosition() const;

    void setOrientation(float w, float x, float y, float z);
    void setOrientation(const glm::quat &ori);
    glm::quat getOrientation() const;

    void setScale(float xScale, float yScale, float zScale);
    void setScale(const glm::vec3 &scale);
    void setScale(float scale);

    const glm::mat4& getModelMatrix() const;
    void render() const;

private:
    Mesh mesh;

    glm::vec3 position;
    glm::quat orientation;
    glm::vec3 scale;

    bool outdated;
    glm::mat4 modelMatrix;
};

#endif