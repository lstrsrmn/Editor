#include "../../include/engine/graphics/ModelImporter.h"

ModelMeshTree* loadDefaultModel(const std::filesystem::path& modelName,const std::filesystem::path& modelPath, bool flipV) {
    // wrapper function for loading default models
    return loadModel(modelPath/modelName, flipV);
}
ModelMeshTree* loadModel(const std::filesystem::path& modelName, bool flipV) {
    // gets the scene from the file
    Assimp::Importer importer;
    const aiScene* modelScene = importer.ReadFile(modelName, aiProcess_Triangulate | aiProcess_GenNormals |
                                                                         aiProcess_CalcTangentSpace | aiProcess_FixInfacingNormals | aiProcess_FindInvalidData | aiProcess_ValidateDataStructure);
    
    // makes sure scene is valid
    if (!modelScene) {
        return nullptr;
    }

//    Mesh** meshes = new Mesh*[modelScene->mNumMeshes];
//
//    for (unsigned int i = 0; i < modelScene->mNumMeshes; i++)
//        meshes[i] = getMeshData(modelScene->mMeshes[i], flipV);

    return getMeshesFromNode(modelScene->mRootNode, modelScene, flipV);
}

Mesh* getMeshData(const aiMesh* mesh, bool flipV) {
    Vertex* vertices = new Vertex[mesh->mNumVertices];
    unsigned int* indices = new unsigned int [mesh->mNumFaces * 3];
    std::string name = std::string(mesh->mName.C_Str(), mesh->mName.length);
    unsigned int id = std::hash<std::string>()(name);
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

    return new Mesh(vertices, mesh->mNumVertices, indices, mesh->mNumFaces * 3, id, name);
}

// recursive function for going down the node tree and transferring the data into my own data structures
ModelMeshTree* getMeshesFromNode(const aiNode* node, const aiScene* scene, bool flipV) {
    ModelMeshTree* tree = new ModelMeshTree();
    tree->transform = aiToGlmMatrix(node->mTransformation);
    tree->meshes.resize(node->mNumMeshes);
    for (int i = 0; i < node->mNumMeshes; i++) {
        tree->meshes[i] = getMeshData(scene->mMeshes[node->mMeshes[i]], flipV);
    }
    tree->children.resize(node->mNumChildren);
    for (int i = 0; i < node->mNumChildren; i++) {
        tree->children[i] = getMeshesFromNode(node->mChildren[i], scene, flipV);
    }
    return tree;
}

// converts between Mats from assimp (the model loader) and opengl (the renderer)
glm::mat4 aiToGlmMatrix(const aiMatrix4x4& aiMat) {
    glm::mat4 glmMat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glmMat[i][j] = aiMat[i][j];
        }
    }
    return glmMat;
}
