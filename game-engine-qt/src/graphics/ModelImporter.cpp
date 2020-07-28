#include "../../include/engine/graphics/ModelImporter.h"

ModelMeshData loadDefaultModel(const std::string& modelName,const std::string& modelPath, bool flipV) {
    return loadModel(modelPath+modelName, flipV);
}
ModelMeshData loadModel(const std::string& modelName, bool flipV) {
    Assimp::Importer importer;
    const aiScene* modelScene = importer.ReadFile(modelName, aiProcess_Triangulate | aiProcess_GenNormals |
                                                                         aiProcess_CalcTangentSpace | aiProcess_FixInfacingNormals | aiProcess_FindInvalidData | aiProcess_ValidateDataStructure);

    if (!modelScene) {
        return {nullptr, std::string()};
    }

//    Mesh** meshes = new Mesh*[modelScene->mNumMeshes];
//
//    for (unsigned int i = 0; i < modelScene->mNumMeshes; i++)
//        meshes[i] = getMeshData(modelScene->mMeshes[i], flipV);

    return {getMeshesFromNode(modelScene->mRootNode, modelScene, flipV), modelName};
}

Mesh* getMeshData(const aiMesh* mesh, bool flipV) {
    Vertex* vertices = new Vertex[mesh->mNumVertices];
    unsigned int* indices = new unsigned int [mesh->mNumFaces * 3];

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 pos(-mesh->mVertices[i].x, mesh->mVertices[i].z, mesh->mVertices[i].y);
        glm::vec2 tex;
        glm::vec3 normal(-mesh->mNormals[i].x, mesh->mNormals[i].z, mesh->mNormals[i].y);
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

ModelMeshTree* getMeshesFromNode(const aiNode* node, const aiScene* scene, bool flipV) {
    ModelMeshTree* tree = new ModelMeshTree();
    tree->transform = aiToGlmMatrix(node->mTransformation);
    tree->numMeshes = node->mNumMeshes;
    tree->meshes = new Mesh*[node->mNumMeshes];
    for (int i = 0; i < node->mNumMeshes; i++) {
        tree->meshes[i] = getMeshData(scene->mMeshes[node->mMeshes[i]], flipV);
    }
    tree->numChildren = node->mNumChildren;
    tree->children = new ModelMeshTree*[node->mNumChildren];
    for (int i = 0; i < node->mNumChildren; i++) {
        tree->children[i] = getMeshesFromNode(node->mChildren[i], scene, flipV);
    }
    return tree;
}

glm::mat4 aiToGlmMatrix(const aiMatrix4x4& aiMat) {
    glm::mat4 glmMat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glmMat[i][j] = aiMat[i][j];
        }
    }
    return glmMat;
}