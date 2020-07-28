#include "GameGLView.h"

GameGLView::GameGLView(QWidget *parent) {
//    create();
}

GameGLView::~GameGLView() {

}

void GameGLView::initializeGL() {
    makeCurrent();
//    context()->setShareContext(ContextController::instance()->getSceneContext());

    QOpenGLFunctions* f = context()->globalShareContext()->functions();

//    f->initializeOpenGLFunctions();
    ContextController::instance()->setGameGL(f, this);


    ContextController::instance()->setCurrent(1);

    _game = Game::instance();
    _game->setGlFunctions(f);

    f->glEnable(GL_DEPTH_TEST);

    f->glEnable(GL_CULL_FACE);

    f->glFrontFace(GL_CCW);
    f->glCullFace(GL_BACK);

    Texture* texture = Texture::createTexture("defaultDIffuse", "res/textures/defaultDiffuse.jpg");
    Shader* shader = Shader::createShader("shader", "basicShader");
    Material* material = Material::createMaterial("testMat", "/home/lstrsrmn/Game-Engine-Projects/test/Assets/Materials", shader, texture);

    Camera* camera = new Camera(glm::vec3(0, 0, 0), 70, (float)width()/height(), 0.0001f, 1000.0f);
    Transform transform;

    ModelMeshData model = loadDefaultModel("Monkey.fbx");

    MeshRenderer* cameraRenderer = new MeshRenderer(material, model);

    DirectionalLight* light = new DirectionalLight();

    _scene = new Scene(camera, light);

    GameObject* cameraObject = _scene->createGameObject();
    cameraObject->setName("cameraObject");

    cameraObject->addComponent(cameraRenderer);
}

void GameGLView::paintGL() {
    if (isEnabled()) {
        _game->update();
        update();
    }
}

void GameGLView::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
    _game->setAR((float)w/(float)h);
}

void GameGLView::bindScene(Scene *scene) {
//    _game = Game::instance();
//    _scene = scene;
//    _game->addScene(_scene);
//    _game->setActive(_scene->getId());
//    _scene->getCamera()->moveTo({0, 1, -5});
}
