#include "Mesh.h"

Mesh::MeshEntry::MeshEntry()
{
    vb = INVALID_OGL_VALUE;
    ib = INVALID_OGL_VALUE;
    NumIndices  = 0;
    MaterialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
    if (vb != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &vb);
    }

    if (ib != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &ib);
    }
}

void Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();

    // Allocate an OpenGL vertex array object.
    glGenVertexArrays(1, &vao);

    // Bind the vertex array object to store all the buffers and vertex attributes we create int it
    glBindVertexArray(vao);

    // Generate an ID for the vertex buffer.
    glGenBuffers(1, &vb);

    // Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    // Enable the three vertex array attributes.
    glEnableVertexAttribArray(0);  // Vertex position.
    glEnableVertexAttribArray(1);  // Texture coordinates.
    glEnableVertexAttribArray(2);  // Normals.

    // Specify the location and format of the position portion of the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

    // Specify the location and format of the texture coordinate portion of the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

    // Specify the location and format of the normal vector portion of the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

    // Generate an ID for the index buffer.
    glGenBuffers(1, &ib);

    // Bind the index buffer and load the index data into it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh(const ConfigParser& config) : numVerticies(0), numFaces(0), config(config)
{
}

bool Mesh::loadMesh(const std::string& fileName)
{
    // Release the previously loaded mesh (if it exists)
    this->textures.clear();
    this->entries.clear();

    bool res = false;
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (pScene) 
    {
        res = this->initFromScene(pScene, fileName);
    }
    else 
    {
        printf("Error parsing '%s': '%s'\n", fileName.c_str(), importer.GetErrorString());
    }

    // print debug info
    printf("Loaded %i verticies\n", this->numVerticies);
    printf("Loaded %i faces\n", this->numFaces);

    return res;
}

bool Mesh::initFromScene(const aiScene* pScene, const std::string& fileName)
{  
    this->entries.resize(pScene->mNumMeshes);
    this->textures.resize(pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < entries.size() ; i++) 
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        this->initMesh(i, paiMesh);
    }

    return this->initMaterials(pScene, fileName);
}

void Mesh::initMesh(unsigned int Index, const aiMesh* paiMesh)
{
    this->entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) 
    {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

        Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
            glm::vec2(pTexCoord->x, pTexCoord->y),
            glm::vec3(pNormal->x, pNormal->y, pNormal->z));

        vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
    {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

    this->entries[Index].Init(vertices, indices);

    // store debug info
    this->numVerticies += paiMesh->mNumVertices;
    this->numFaces += paiMesh->mNumFaces;
}

bool Mesh::initMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type slashIndex = Filename.find_last_of("/");
    std::string dir;

    if (slashIndex == std::string::npos) 
    {
        dir = ".";
    }
    else if (slashIndex == 0) 
    {
        dir = "/";
    }
    else 
    {
        dir = Filename.substr(0, slashIndex);
    }

    bool res = true;

    // Initialize the materials
    for (unsigned int i = 0; i < pScene->mNumMaterials; i++) 
    {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
        {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_UNKNOWN, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
            {
                StringPathUPtr sp = processPath(std::string(Path.data));

                std::string FullPath = dir + "/" + sp->filename;
                textures[i] = std::unique_ptr<Texture>(new Texture(GL_TEXTURE_2D, FullPath.c_str()));

                if (!textures[i]->load()) 
                {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    res = false;
                }
                else 
                {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }

        // Load a white texture in case the model does not include its own texture
        if (!textures[i]) 
        {
            textures[i] = std::unique_ptr<Texture>(new Texture(GL_TEXTURE_2D, config.getFallbackTexture()));
            res = textures[i]->load();
        }
    }

    return res;
}

void Mesh::render() const
{
    for (unsigned int i = 0; i < entries.size(); i++) 
    {
        glBindVertexArray(entries[i].vao);

        const unsigned int materialIndex = entries[i].MaterialIndex;

        if (materialIndex < textures.size() && textures[materialIndex]) {
            textures[materialIndex]->bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

}