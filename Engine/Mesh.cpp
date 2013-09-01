#include "Mesh.h"

Mesh::MeshEntry::MeshEntry()
{
    VB = INVALID_OGL_VALUE;
    IB = INVALID_OGL_VALUE;
    NumIndices  = 0;
    MaterialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
    if (VB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &VB);
    }

    if (IB != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &IB);
    }
}

void Mesh::MeshEntry::Init(const std::vector<Vertex>& Vertices,
                           const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();

    // Allocate an OpenGL vertex array object.
    glGenVertexArrays(1, &VAO);

    // Bind the vertex array object to store all the buffers and vertex attributes we create int it
    glBindVertexArray(VAO);

    // Generate an ID for the vertex buffer.
    glGenBuffers(1, &VB);

    // Bind the vertex buffer and load the vertex (position, texture, and normal) data into the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    // Enable the three vertex array attributes.
    glEnableVertexAttribArray(0);  // Vertex position.
    glEnableVertexAttribArray(1);  // Texture coordinates.
    glEnableVertexAttribArray(2);  // Normals.

    // Specify the location and format of the position portion of the vertex buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

    // Specify the location and format of the texture coordinate portion of the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

    // Specify the location and format of the normal vector portion of the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

    // Generate an ID for the index buffer.
    glGenBuffers(1, &IB);

    // Bind the index buffer and load the index data into it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh() : numVerticies(0), numFaces(0)
{
}


Mesh::~Mesh()
{
    clear();
}


void Mesh::clear()
{
    for (unsigned int i = 0 ; i < m_Textures.size() ; i++) {
        if(m_Textures[i])
        {
            delete m_Textures[i];
            m_Textures[i] = NULL;
        }
    }
}


bool Mesh::loadMesh(const std::string& Filename)
{
    // Release the previously loaded mesh (if it exists)
    clear();

    bool Ret = false;
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (pScene) {
        Ret = initFromScene(pScene, Filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }

    // print debug info
    printf("Loaded %i verticies\n", this->numVerticies);
    printf("Loaded %i faces\n", this->numFaces);

    return Ret;
}

bool Mesh::initFromScene(const aiScene* pScene, const std::string& Filename)
{  
    m_Entries.resize(pScene->mNumMeshes);
    m_Textures.resize(pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        initMesh(i, paiMesh);
    }

    return initMaterials(pScene, Filename);
}

void Mesh::initMesh(unsigned int Index, const aiMesh* paiMesh)
{
    m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
            glm::vec2(pTexCoord->x, pTexCoord->y),
            glm::vec3(pNormal->x, pNormal->y, pNormal->z));

        Vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

    m_Entries[Index].Init(Vertices, Indices);

    // store debug info
    this->numVerticies += paiMesh->mNumVertices;
    this->numFaces += paiMesh->mNumFaces;
}

bool Mesh::initMaterials(const aiScene* pScene, const std::string& Filename)
{
    // Extract the directory part from the file name
    std::string::size_type SlashIndex = Filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = Filename.substr(0, SlashIndex);
    }

    bool Ret = true;

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        m_Textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + Path.data;
                m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

                if (!m_Textures[i]->Load()) {
                    printf("Error loading texture '%s'\n", FullPath.c_str());
                    delete m_Textures[i];
                    m_Textures[i] = NULL;
                    Ret = false;
                }
                else {
                    printf("Loaded texture '%s'\n", FullPath.c_str());
                }
            }
        }

        // Load a white texture in case the model does not include its own texture
        if (!m_Textures[i]) {
            m_Textures[i] = new Texture(GL_TEXTURE_2D, "white.png");

            Ret = m_Textures[i]->Load();
        }
    }

    return Ret;
}

void Mesh::render()
{
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) 
    {
        glBindVertexArray(m_Entries[i].VAO);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
            m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

}