#include "../../include/engine/graphics/ModelImporter.h"

ModelMeshData loadModel(const std::string& modelName,const std::string& modelPath, bool flipV) {
    Assimp::Importer importer;
    const aiScene* modelScene = importer.ReadFile(modelPath + modelName, aiProcess_Triangulate | aiProcess_GenNormals |
    aiProcess_CalcTangentSpace | aiProcess_FixInfacingNormals | aiProcess_FindInvalidData | aiProcess_ValidateDataStructure);

    if (!modelScene) {
        return {};
    }

    Mesh** meshes = new Mesh*[modelScene->mNumMeshes];

    for (unsigned int i = 0; i < modelScene->mNumMeshes; i++)
        meshes[i] = getMeshData(modelScene->mMeshes[i], flipV);

    return {meshes, modelScene->mNumMeshes};
}

Mesh* getMeshData(const aiMesh* mesh, bool flipV) {
    Vertex* vertices = new Vertex[mesh->mNumVertices];
    unsigned int* indices = new unsigned int [mesh->mNumFaces * 3];

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 pos(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        glm::vec2 tex;
        glm::vec3 normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->HasTextureCoords(0)) {
            tex.x = mesh->mTextureCoords[0][i].x;
            tex.y = flipV ? 1 - mesh->mTextureCoords[0][i].y : mesh->mTextureCoords[0][i].y;
        }
        else {
            tex.x = 0;
            tex.y = 0;
        }

        Vertex v = {
                .pos = pos,
                .texCoord = tex,
                .normal = normal
        };
        vertices[i] = v;
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace* face = &mesh->mFaces[i];
        indices[i * 3] = face->mIndices[0];
        indices[i * 3 + 1] = face->mIndices[1];
        indices[i * 3 + 2] = face->mIndices[2];
    }
    return new Mesh(vertices, mesh->mNumVertices, indices, mesh->mNumFaces * 3);
}