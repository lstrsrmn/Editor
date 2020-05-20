#ifndef GAME_ENGINE_MODELIMPORTER_H
#define GAME_ENGINE_MODELIMPORTER_H

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

ModelMeshData loadModel(const std::string&, const std::string& = "res/models/default/", bool flipV = true);

Mesh* getMeshData(const aiMesh*, bool flipV);

#endif //GAME_ENGINE_MODELIMPORTER_H
