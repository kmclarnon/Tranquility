#ifndef _TRANQUILITYMESH_H_
#define _TRANQUILITYMESH_H_

#include "Common.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.h"
#include "ConfigParser.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex;
    glm::vec3 normal;

    Vertex() {}

    Vertex(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& normal)
    {
        this->pos    = pos;
        this->tex    = tex;
        this->normal = normal;
    }
};


class Mesh
{
public:
    Mesh(const ConfigParser &config);

    bool loadMesh(const std::string& Filename);
    void render() const;

private:
    bool initFromScene(const aiScene* pScene, const std::string& Filename);
    void initMesh(unsigned int Index, const aiMesh* paiMesh);
    bool initMaterials(const aiScene* pScene, const std::string& Filename);


    struct MeshEntry 
    {
        MeshEntry();
        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
            const std::vector<unsigned int>& Indices);

        GLuint vb;
        GLuint ib;
        GLuint vao;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> entries;
    std::vector<std::unique_ptr<Texture>> textures;

    // we don't own this
    const ConfigParser &config;

    //debug info
    int numVerticies;
    int numFaces;
};

#endif