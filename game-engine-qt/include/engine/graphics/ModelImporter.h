#ifndef GAME_ENGINE_MODELIMPORTER_H
#define GAME_ENGINE_MODELIMPORTER_H

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

struct ModelMeshData;
struct ModelMeshTree;
class Mesh;

ModelMeshData loadDefaultModel(const std::string&, const std::string& = "res/models/default/", bool flipV = true);
ModelMeshData loadModel(const std::string&, bool flipV = true);

Mesh* getMeshData(const aiMesh*, bool flipV);
ModelMeshTree* getMeshesFromNode(const aiNode*, const aiScene*, bool flipV);
glm::mat4 aiToGlmMatrix(const aiMatrix4x4&);
#endif //GAME_ENGINE_MODELIMPORTER_H
