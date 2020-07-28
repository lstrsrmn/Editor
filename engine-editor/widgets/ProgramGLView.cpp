//
// Created by lstrsrmn on 06/07/2020.
//

#include "ProgramGLView.h"

ProgramGLView::ProgramGLView(QWidget *parent) {

}

void ProgramGLView::initializeGL() {

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    context()->create();
    makeCurrent();
    QOpenGLWidget::initializeGL();

    QOpenGLFunctions* f = context()->functions();

    ContextController::setGL(f, this);

    _game = Game::instance();
    _game->setGlFunctions(f);

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
    _scene = new Scene(_sceneView->getCamera(), light);
    _scene->setName("Test Scene");
    _sceneView->addScene(_scene);
    _sceneView->setActive(_scene->getId());
}

void ProgramGLView::paintGL() {
    if (_viewPortState == SCENE) {
        _sceneView->update();
    }
    else if (_viewPortState == GAME) {
        if (_gameEnabled) {
            _game->update();
        }
    }
    update();
}

void ProgramGLView::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
    updateSize();
}

void ProgramGLView::mousePressEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    _mouseStartPos = event->globalPos();
    if (_viewPortState == SCENE) {
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
            default:
                break;
        }
    }
    if (_viewPortState == GAME) {
        switch (event->button()) {
            default:
                break;
        }
    }
}

void ProgramGLView::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    QPoint centre = mapToGlobal(QPoint(size().width()/2, size().height()/2));
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
    if(_gameActive) {
        QCursor::setPos(centre);
    }
}

void ProgramGLView::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    if (_viewPortState == SCENE) {
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
    else {
        switch (event->button()) {
            case Qt::LeftButton:
                if (!_gameActive) {
                    setCursor(Qt::BlankCursor);
                    _gameActive = true;
                }
                break;
            default:
                break;
        }
    }
}

void ProgramGLView::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);
    if (_viewPortState == SCENE) {
        float delta = event->angleDelta().y();
        _sceneView->zoom(-delta / 120);
    }
}

void ProgramGLView::setViewFocus(glm::vec3 pos) {
    if (_viewPortState == SCENE) {
        _sceneView->setFocus(pos);
    }
}

void ProgramGLView::bindScene(Scene* scene) {
    _game = Game::instance();
    _scene = scene;
    _game->addScene(_scene);
    _game->setActive(_scene->getId());
    _scene->getCamera()->moveTo({0, 1, -5});
    _sceneView->getCamera()->moveTo({0, 1, -10});
    _scene->setName("Test Scene");
    _sceneView->addScene(_scene);
    _sceneView->setActive(_scene->getId());
}

void ProgramGLView::changeViewPort(ViewPortState state) {
    _viewPortState = state;
}

void ProgramGLView::changeGameEnabled(bool enabled) {
    _gameEnabled = enabled;
}

void ProgramGLView::keyPressEvent(QKeyEvent* event) {
    if (_viewPortState == GAME) {
        switch (event->key()) {
            case Qt::Key_Escape:
                if (_gameActive) {
                    unsetCursor();
                  _gameActive = false;
                }
                else if (!_gameActive) {
                    setCursor(Qt::BlankCursor);
                    _gameActive = true;
                }
                break;
            default:
                break;
        }
    }
}

void ProgramGLView::updateSize() {
    _sceneView->setAR((float) width() /(float) height());
    _game->setAR((float)width()/(float)height());
}

