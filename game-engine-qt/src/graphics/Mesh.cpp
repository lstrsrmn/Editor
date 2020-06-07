
#include <vector>
#include <iostream>
#include "../../include/engine/graphics/Mesh.h"
#include "../../include/engine/game/ContextController.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, bool sceneMode) {
    _drawCount = numIndices;
//    if (sceneMode) {
        ContextController::instance()->setCurrent(0);
        QOpenGLFunctions *sceneF = ContextController::instance()->getCurrentFunctions();

        sVAO = new QOpenGLVertexArrayObject();
        sVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        sIBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

        sVAO->create();
        sVBO->create();
        sIBO->create();

        sVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
        sIBO->setUsagePattern(QOpenGLBuffer::StaticDraw);

        sVAO->bind();
        sVBO->bind();
        sIBO->bind();
        sIBO->allocate(indices, numIndices * sizeof(unsigned int));
        sVBO->allocate(vertices, numVertices * sizeof(Vertex));
        sceneF->glEnableVertexAttribArray(0);
        sceneF->glEnableVertexAttribArray(1);
        sceneF->glEnableVertexAttribArray(2);
        sceneF->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
        sceneF->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
        sceneF->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (5 * sizeof(GLfloat)));
        sVAO->release();
//    }
//    ContextController::instance()->setCurrent(1);
//    QOpenGLFunctions* gameF = ContextController::instance()->getCurrentFunctions();
//
//    gVAO = new QOpenGLVertexArrayObject();
//    gVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//    gIBO = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//
//    gVAO->create();
//    gVBO->create();
//    gIBO->create();
//
//    gVBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
//    gIBO->setUsagePattern(QOpenGLBuffer::StaticDraw);
//
//    gVAO->bind();
//    gVBO->bind();
//    gIBO->bind();
//    gIBO->allocate(indices, numIndices * sizeof(unsigned int));
//    gVBO->allocate(vertices, numVertices * sizeof(Vertex));
//    gameF->glEnableVertexAttribArray(0);
//    gameF->glEnableVertexAttribArray(1);
//    gameF->glEnableVertexAttribArray(2);
//    gameF->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
//    gameF->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//    gameF->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
//    gVAO->release();
//    if (sceneMode)
//        ContextController::instance()->setCurrent(0);
}

void Mesh::draw() const {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentFunctions();
//    if (ContextController::instance()->getCurrent()) {
        sVAO->bind();
        sVBO->bind();
        sIBO->bind();
        f->glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);
        sVAO->release();
        sIBO->release();
        sVBO->release();
//    }
//    else {
//        gVAO->bind();
//        gVBO->bind();
//        gIBO->bind();
//        f->glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, nullptr);
//        gVAO->release();
//        gIBO->release();
//        gVBO->release();
//    }

//    std::cout << f->glGetError() << std::endl;

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
    sVAO->destroy();
    sVBO->destroy();
    sIBO->destroy();
//    gVAO->destroy();
//    gVBO->destroy();
//    gIBO->destroy();

//    f->glDeleteBuffers(NUM_BUFFERS, _vertexArrayBuffers);
//    f->glDeleteVertexArrays(1, &_vertexArrayObject);
}

