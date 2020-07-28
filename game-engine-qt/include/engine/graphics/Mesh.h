#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <glm/glm.hpp>
#include <QtOpenGL>
#include <string>
#include <QOpenGLVertexArrayObject>
//#include "../game/ContextController.h"

class Mesh;

struct ModelMeshTree {
    Mesh **meshes;
    unsigned int numMeshes;
    ModelMeshTree** children;
    unsigned int numChildren;
    glm::mat4 transform;
};

struct ModelMeshData {
    ModelMeshTree* tree;
    std::filesystem::path filePath;
};
struct Vertex {
    glm::vec3 pos{};
    glm::vec2 texCoord{};
    glm::vec3 normal{};
};


class Mesh {
public:
    Mesh(Vertex *, unsigned int, unsigned int *, unsigned int, bool = true);

    void draw() const;

    virtual ~Mesh();

private:
    Mesh(const Mesh &other) = default;

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

    unsigned int _drawCount;
};


#endif //GAME_ENGINE_MESH_H
