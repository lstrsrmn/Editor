//
// Created by lstrsrmn on 19/05/2020.
//

#include "SceneGLView.h"

SceneGLView::SceneGLView(QWidget *parent) {
    create();
}

SceneGLView::~SceneGLView() {

}

void SceneGLView::initializeGL() {
//    QOpenGLWidget::initializeGL();
    makeCurrent();
    QOpenGLFunctions *f = context()->functions();
    f->initializeOpenGLFunctions();
    ContextController::instance()->setSceneGLFunctions(f);

//    makeCurrent();

    _sceneView = SceneView::instance();
    _sceneView->setGlFunctions(f);
    _sceneView->setAR((float) width() / height());
    _sceneView->makeCamera();
    f->glEnable(GL_DEPTH_TEST);

    f->glEnable(GL_CULL_FACE);

    f->glFrontFace(GL_CCW);
    f->glCullFace(GL_BACK);

    Texture *texture = new Texture("monkeyDiffuse2.jpg");
    Shader *shader = new Shader("basicShader");

    _material = new Material(shader, texture);

    DirectionalLight *light = new DirectionalLight(glm::vec3(0, -1, 0), glm::vec3(1, 1, 1));

    _sceneView->getCamera()->moveTo({0, 1, -10});
    _scene = new Scene(_sceneView->getCamera(), *light);
    _scene->setName("Test Scene");
    _sceneView->addScene(_scene);
    _sceneView->setActive(_scene->getId());
    ModelMeshData monkey = loadModel("Monkey.fbx");
    ModelMeshData plane = loadModel("Plane.fbx");

    MeshRenderer *mRenderer = new MeshRenderer(_material, monkey);
    MeshRenderer* pRenderer = new MeshRenderer(_material, plane);

    GameObject *mObj = _scene->createGameObject();
    GameObject *pObj = _scene->createGameObject();
    mObj->setName("Monkey");
    pObj->setName("Plane");

    mObj->addComponent(mRenderer);
    pObj->addComponent(pRenderer);

    mObj->getTransform().setRot(glm::vec3(3.1415 / 2, 0, 3.1415));
    mObj->getTransform().setPos({0, 1, 0});
    pObj->getTransform().setRot(glm::vec3(3.1415 / 2, 0, 3.1415));
}

void SceneGLView::paintGL() {
    _sceneView->update();
    update();
}

void SceneGLView::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
    _sceneView->setAR((float) w / h);
}

void SceneGLView::mousePressEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    _mouseStartPos = event->globalPos();
    switch (event->button()) {
        case Qt::LeftButton:
            break;
        case Qt::RightButton:
            setCursor(Qt::BlankCursor);
            _orbit = true;
            break;
        case Qt::MiddleButton:
            setCursor(Qt::BlankCursor);
            _pan = true;
            break;
        case Qt::ExtraButton1:
            break;
    }
}

void SceneGLView::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    QPoint current = event->globalPos();
    int dx = current.x() - _mouseStartPos.x();
    int dy = current.y() - _mouseStartPos.y();
    if (_pan) {
        _sceneView->pan({dx, dy});
        QCursor::setPos(_mouseStartPos);
    }
    if (_orbit) {
        _sceneView->orbit({dx, dy});
        QCursor::setPos(_mouseStartPos);
    }
}

void SceneGLView::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    switch (event->button()) {
        case Qt::LeftButton:
            unsetCursor();
            break;
        case Qt::RightButton:
            _orbit = false;
            break;
        case Qt::MiddleButton:
            unsetCursor();
            _pan = false;
            break;
        case Qt::ExtraButton1:
            break;
    }
}
