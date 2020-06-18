#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <glm/glm.hpp>
#include <QtOpenGL>
#include <string>
#include <assimp/Importer.hpp>
#include "../game/Game.h"
#include <QOpenGLVertexArrayObject>
//#include "../game/ContextController.h"

class Mesh;

struct ModelMeshData {
    Mesh **meshes;
    unsigned int numMeshes;
    std::string filePath;
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
    QOpenGLVertexArrayObject *sVAO, *gVAO;
    QOpenGLBuffer *sVBO, *gVBO;
    QOpenGLBuffer *sIBO, *gIBO;

    unsigned int _drawCount;
};


#endif //GAME_ENGINE_MESH_H
