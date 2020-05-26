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
    f->glEnable(GL_DEPTH_TEST);

    f->glEnable(GL_CULL_FACE);

    f->glFrontFace(GL_CCW);
    f->glCullFace(GL_BACK);

    DirectionalLight light;

    Camera* camera = new Camera({0, 1, 0}, 80, _game->getAR(), 0.001f, 1000.0f);

    bindScene(new Scene(camera, light));

    _game->setAR((float)width()/height());
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