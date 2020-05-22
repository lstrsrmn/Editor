#include "GameGLView.h"

GameGLView::GameGLView(QWidget *parent) {
    create();
}

GameGLView::~GameGLView() {

}

void GameGLView::initializeGL() {
    makeCurrent();
    QOpenGLFunctions* f = context()->functions();
    f->initializeOpenGLFunctions();
    ContextController::instance()->setGameGLFunctions(f, this);

    _game = Game::instance();
    _game->setGlFunctions(f);
    _game->makeDisplay(width(), height(), "gameEditor");
    f->glEnable(GL_DEPTH_TEST);

    f->glEnable(GL_CULL_FACE);

    f->glFrontFace(GL_CCW);
    f->glCullFace(GL_BACK);

    Texture* texture = new Texture("monkeyDiffuse2.jpg");
    Shader* shader = new Shader("basicShader");

    _material = new Material(shader, texture);
    Camera* camera = new Camera(glm::vec3(0, 0, -5), 70.0f, _game->getAR(), 0.01f, 1000.0f);

    DirectionalLight* light = new DirectionalLight(glm::vec3(0, 1, 0), glm::vec3(1, 1, 1));

    _scene = new Scene(camera, *light);
    _game->addScene(_scene);
    _game->setActive(_scene->getId());
    ModelMeshData monkey = loadModel("Monkey.fbx");
    ModelMeshData plane = loadModel("Plane.fbx");

    MeshRenderer* mRenderer = new MeshRenderer(_material, monkey);
    MeshRenderer* pRenderer = new MeshRenderer(_material, plane);

    GameObject *mObj = _scene->createGameObject();
    GameObject *pObj = _scene->createGameObject();

    mObj->addComponent(mRenderer);
    pObj->addComponent(pRenderer);

    mObj->setName("Monkey");
    pObj->setName("Plane");

    mObj->getTransform().setRot(glm::vec3(3.1415 / 2, 0, 3.1415));
    pObj->getTransform().setRot(glm::vec3(3.1415 / 2, 0, 3.1415));
    _initialised = true;
}

void GameGLView::paintGL() {
    if (isEnabled()) {
        Game::instance()->update();
        update();
    }
}

void GameGLView::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
    _game->setAR((float)w/(float)h);
}

void GameGLView::bindScene(Scene *scene) {
    _scene = scene;
    _game->addScene(_scene);
    _game->setActive(_scene->getId());
}