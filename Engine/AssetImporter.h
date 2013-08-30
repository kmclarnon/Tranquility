#ifndef _TRILLEK_ASSET_IMPORTER_H_
#define _TRILLEK_ASSET_IMPORTER_H_

#include "Common.h"
#include "LogSystem.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class AssetImporter
{
public:
    AssetImporter(LogSystem &log);

    bool importMesh(const std::string& file, Mesh &mesh);

private:
    // We do not own this
    LogSystem &logSys;
};

#endif