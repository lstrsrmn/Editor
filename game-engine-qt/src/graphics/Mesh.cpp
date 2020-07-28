#include <iostream>
#include "../../include/engine/graphics/Mesh.h"
#include "../../include/engine/game/ContextController.h"

Mesh::Mesh(Vertex *vertices, unsigned int numVertices, unsigned int *indices, unsigned int numIndices, bool sceneMode) {
    _drawCount = numIndices;
    QOpenGLFunctions *f = ContextController::getFunctions();

    VAO = new QOpenGLVertexArrayObject();
    VBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    IBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    VAO->create();
    VBO->create();
    IBO->create();

    VBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
    IBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

    VAO->bind();
    VBO->bind();
    IBO->bind();
    IBO->allocate(indices, numIndices * sizeof(unsigned int));
    VBO->allocate(vertices, numVertices * sizeof(Vertex));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));
    VAO->release();
    VBO->release();
    IBO->release();
}

void Mesh::draw() const {
    QOpenGLFunctions *f = ContextController::getFunctions();
    VAO->bind();
    VBO->bind();
    IBO->bind();
    f->glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);
    VAO->release();
    IBO->release();
    VBO->release();
}

Mesh::~Mesh() {
    VAO->destroy();
    VBO->destroy();
    IBO->destroy();
}

