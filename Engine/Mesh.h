#ifndef _TRILLEK_MESH_H_
#define _TRILLEK_MESH_H_

#include "Common.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.h"

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
    Mesh();

    ~Mesh();

    bool loadMesh(const std::string& Filename);
    void render();

private:
    bool initFromScene(const aiScene* pScene, const std::string& Filename);
    void initMesh(unsigned int Index, const aiMesh* paiMesh);
    bool initMaterials(const aiScene* pScene, const std::string& Filename);
    void clear();


    struct MeshEntry 
    {
        MeshEntry();
        ~MeshEntry();

        void Init(const std::vector<Vertex>& Vertices,
            const std::vector<unsigned int>& Indices);

        GLuint VB;
        GLuint IB;
        GLuint VAO;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::vector<MeshEntry> m_Entries;
    std::vector<Texture*> m_Textures;

    //debug info
    int numVerticies;
    int numFaces;
};

#endif