#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <QtOpenGL>
#include <string>
#include <QOpenGLVertexArrayObject>
#include <filesystem>
#include <assimp/mesh.h>
#include "../core/AssetManager.h"

class Mesh;

struct ModelMeshTree {
    std::vector<Mesh*> meshes;
    std::vector<ModelMeshTree*> children;
    glm::mat4 transform;
};

class ModelMeshData : public Asset {
    ASSET(ModelMeshData)
public:
    static ModelMeshData* createModelMeshData(const std::string&, const std::filesystem::path&);
    Mesh* getSubMesh(unsigned int);

    ModelMeshTree* tree;
private:
    ModelMeshData(const std::filesystem::path&, unsigned int);
    void setMeshParent(ModelMeshTree*);
    Mesh* findSubMesh(unsigned int, ModelMeshTree*);
};



struct Vertex {
    glm::vec3 pos{};
    glm::vec2 texCoord{};
    glm::vec3 normal{};
};


class Mesh{
    friend class ModelMeshData;
    friend Mesh* getMeshData(const aiMesh*, bool flipV);
public:
    void draw() const;

    virtual ~Mesh();

    std::string name;

    ModelMeshData *getModelMeshData() const;

    unsigned int getID() const;

private:
    Mesh(Vertex *, unsigned int, unsigned int *, unsigned int, unsigned int, std::string = "", bool = true);
    Mesh(const Mesh &other) = default;
    ModelMeshData* parent = nullptr;
    unsigned int id;
    unsigned int _drawCount;

    enum {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS
    };
    QOpenGLVertexArrayObject *VAO;
    QOpenGLBuffer *VBO;
    QOpenGLBuffer *IBO;
};


#endif //GAME_ENGINE_MESH_H
