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

// forward declaration of mesh
class Mesh;

// defines tree for object internal hierarchy
struct ModelMeshTree {
    std::vector<Mesh*> meshes;
    std::vector<ModelMeshTree*> children;
    glm::mat4 transform;
};

// creates nodes for tree, as asset
class ModelMeshData : public Asset {
    ASSET(ModelMeshData)
public:
    // public method for creating ModelMeshData
    static ModelMeshData* createModelMeshData(const std::string&, const std::filesystem::path&);
    // get sub meshes of ModelMeshData
    Mesh* getSubMesh(unsigned int);
    
    // stores tree connected to, to make doubly linked tree
    ModelMeshTree* tree;
private:
    // private constructor
    ModelMeshData(const std::filesystem::path&, unsigned int);
    // assigns meshs parent
    void setMeshParent(ModelMeshTree*);
    // searches for a sub mesh
    Mesh* findSubMesh(unsigned int, ModelMeshTree*);
};


// creates the Vertex struct with necicary variables
struct Vertex {
    glm::vec3 pos{};
    glm::vec2 texCoord{};
    glm::vec3 normal{};
};

// defines individual mesh class
class Mesh{
    // friends ModelMeshData so private functions have access
    friend class ModelMeshData;
    friend Mesh* getMeshData(const aiMesh*, bool flipV);
public:
    // draws mesh to context
    void draw() const;

    virtual ~Mesh();
    
    std::string name;

    // returns tree
    ModelMeshData *getModelMeshData() const;

    unsigned int getID() const;

private:
    // private constructor
    Mesh(Vertex *, unsigned int, unsigned int *, unsigned int, unsigned int, std::string = "", bool = true);
    // copy constructor
    Mesh(const Mesh &other) = default;
    // assigns parent
    ModelMeshData* parent = nullptr;
    // assgins UID
    unsigned int id;
    // knows how many vertices to draw
    unsigned int _drawCount;
    
    enum {
        POSITION_VB,
        TEXCOORD_VB,
        NORMAL_VB,

        INDEX_VB,

        NUM_BUFFERS
    };
    // creates necicary opengl objects
    QOpenGLVertexArrayObject *VAO;
    QOpenGLBuffer *VBO;
    QOpenGLBuffer *IBO;
};


#endif //GAME_ENGINE_MESH_H
