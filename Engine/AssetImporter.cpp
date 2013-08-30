#include "assetimporter.h"

AssetImporter::AssetImporter(LogSystem &log) : logSys(log)
{

}

bool AssetImporter::importMesh(const std::string& file, Mesh &mesh)
{
    /*
    int pointCount;

    const aiScene* scene = aiImportFile (file.c_str(), aiProcess_Triangulate);
    if (!scene) {
        this->logSys.error("Failed to read mesh %s", file.c_str());
        return false;
    }

    this->logSys.debug("Reading mesh file %s", file.c_str());
    this->logSys.debug("%i animations", scene->mNumAnimations);
    this->logSys.debug("%i cameras", scene->mNumCameras);
    this->logSys.debug("%i lights", scene->mNumLights);
    this->logSys.debug("%i materials", scene->mNumMaterials);
    this->logSys.debug("%i meshes", scene->mNumMeshes);
    this->logSys.debug("%i textures", scene->mNumTextures);

    for (unsigned int m_i = 0; m_i < scene->mNumMeshes; m_i++) 
    {
        const aiMesh* sceneMesh = scene->mMeshes[m_i];
        this->logSys.debug("%i vertices in mesh\n", sceneMesh->mNumVertices);

        pointCount = sceneMesh->mNumVertices;

        for (unsigned int v_i = 0; v_i < sceneMesh->mNumVertices; v_i++) {
            if (sceneMesh->HasPositions ()) 
            {
                const aiVector3D* vp = &(sceneMesh->mVertices[v_i]);
                mesh.addVertex(vp->x, vp->y, vp->z);
            }
            if (sceneMesh->HasNormals ()) 
            {
                const aiVector3D* vn = &(sceneMesh->mNormals[v_i]);
                mesh.addNormal(vn->x, vn->y, vn->z);
            }
            if (sceneMesh->HasTextureCoords (0)) 
            {
                const aiVector3D* vt = &(sceneMesh->mTextureCoords[0][v_i]);
                mesh.addTexCoord(vt->x, vt->y);
            }
            if (sceneMesh->HasTangentsAndBitangents ()) 
            {
                // TODO: store these later
            }
        }
    }

    aiReleaseImport(scene);
    */
    return true;
}