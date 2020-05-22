
#include <vector>
#include "../../include/engine/graphics/Mesh.h"
#include "../../include/engine/game/ContextController.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices) {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    _drawCount = numIndices;

    vertexArrayObject = new QOpenGLVertexArrayObject();
    vertexBufferObject = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    indexBufferObject = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    vertexArrayObject->create();
    vertexBufferObject->create();
    indexBufferObject->create();

    vertexBufferObject->setUsagePattern(QOpenGLBuffer::StaticDraw);
    indexBufferObject->setUsagePattern(QOpenGLBuffer::StaticDraw);

    vertexArrayObject->bind();
    vertexBufferObject->bind();
    indexBufferObject->bind();
    indexBufferObject->allocate(indices, numIndices * sizeof(unsigned int));
    vertexBufferObject->allocate(vertices, numVertices * sizeof(Vertex));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    vertexArrayObject->release();
//    vertexBufferObject->setUsagePattern(QOpenGLBuffer::StaticDraw);

//    f->glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);
//    f->glGenVertexArrays(1, &_vertexArrayObject);
//    f->glBindVertexArray(_vertexArrayObject);

//    std::vector<glm::vec3> positions;
//    std::vector<glm::vec2> texCoords;
//    std::vector<glm::vec3> normals;

//    positions.reserve(numVertices);
//    texCoords.reserve(numVertices);
//    normals.reserve(numVertices);

//    for (unsigned int i = 0; i < numVertices; i++) {
//        positions.push_back(vertices[i].pos);
//        texCoords.push_back(vertices[i].texCoord);
//        normals.push_back(vertices[i].normal);
//    }
//
//    f->glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
//    f->glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
//
//    f->glEnableVertexAttribArray(0);
//    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
//
//    f->glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
//    f->glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);
//
//    f->glEnableVertexAttribArray(1);
//    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
//
//    f->glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
//    f->glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
//
//    f->glEnableVertexAttribArray(2);
//    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
//
//    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
//    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);
//
//    f->glBindVertexArray(0);
}

void Mesh::draw() const {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    vertexArrayObject->bind();
    vertexBufferObject->bind();
    indexBufferObject->bind();
    f->glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);
    vertexArrayObject->release();
    indexBufferObject->release();
    vertexBufferObject->release();

//    f->glBindVertexArray(_vertexArrayObject);
//    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
//    f->glEnableVertexAttribArray(0);
//    f->glEnableVertexAttribArray(1);
//    f->glEnableVertexAttribArray(2);

//    glDrawArrays(GL_TRIANGLES, 0, _drawCount);
//    f->glDrawElementsBaseVertex(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr, 0);
//    f->glDrawArraysInstanced(GL_TRIANGLES, 0, _drawCount, 0);
//    f->glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);

//    f->glBindVertexArray(0);
//    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//    f->glDisableVertexAttribArray(0);
//    f->glDisableVertexAttribArray(1);
//    f->glDisableVertexAttribArray(2);
}

Mesh::~Mesh() {
    vertexArrayObject->destroy();
    vertexBufferObject->destroy();
    indexBufferObject->destroy();

//    f->glDeleteBuffers(NUM_BUFFERS, _vertexArrayBuffers);
//    f->glDeleteVertexArrays(1, &_vertexArrayObject);
}

