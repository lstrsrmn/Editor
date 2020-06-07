//
// Created by lstrsrmn on 19/05/2020.
//

#include "SceneGLView.h"

SceneGLView::SceneGLView(QWidget *parent) {
//    create();
//    ContextController::instance()->setSceneGLCallbacks(std::bind(&SceneGLView::makeCurrent, this), std::bind(&SceneGLView::createContextFunctions, this));
}

SceneGLView::~SceneGLView() {

}

void SceneGLView::initializeGL() {
    QOpenGLFunctions *f = context()->globalShareContext()->functions();
//    f->initializeOpenGLFunctions();
    ContextController::instance()->setSceneGL(f, this);

    ContextController::instance()->setCurrent(0);

    _sceneView = SceneView::instance();
    _sceneView->setGlFunctions(f);
    _sceneView->setAR((float) width() / height());
    _sceneView->makeCamera();
    f->glEnable(GL_DEPTH_TEST);

    f->glEnable(GL_CULL_FACE);

    f->glFrontFace(GL_CCW);
    f->glCullFace(GL_BACK);

    DirectionalLight *light = new DirectionalLight(glm::vec3(0, -1, 0), glm::vec3(1, 1, 1));

    _sceneView->getCamera()->moveTo({0, 1, -10});
    _scene = new Scene(_sceneView->getCamera(), *light);
    _scene->setName("Test Scene");
    _sceneView->addScene(_scene);
    _sceneView->setActive(_scene->getId());

//    GameObject* cameraObject = _scene->createGameObject();
//    cameraObject->setName("cameraObject");
//    ModelMeshData camera = loadDefaultModel("Camera.fbx");
//    Texture* texture = Texture::createTexture("/home/lstrsrmn/CLionProjects/Editor/engine-editor/res/textures/defaultDiffuse.jpg");
//    Shader* shader = new Shader("/home/lstrsrmn/CLionProjects/Editor/engine-editor/res/shaders/basicShader");
//    Material* material = new Material(shader, texture);
//    MeshRenderer* cameraRenderer = new MeshRenderer(material, camera);
//    cameraObject->addComponent(cameraRenderer);
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
            break;
        case Qt::RightButton:
            unsetCursor();
            _orbit = false;
            break;
        case Qt::MiddleButton:
            unsetCursor();
            _pan = false;
            break;
        case Qt::ExtraButton1:
            break;
        default:
            break;
    }
}

void SceneGLView::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    float delta = event->angleDelta().y();
    _sceneView->zoom(-delta/120);
}

void SceneGLView::setFocus(glm::vec3 pos) {
    _sceneView->setFocus(pos);
}