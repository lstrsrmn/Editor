//
// Created by lstrsrmn on 19/05/2020.
//

#include "../../include/engine/game/ContextController.h"

ContextController *ContextController::_instance = nullptr;

ContextController *ContextController::instance() {
    if (_instance == nullptr) {
        _instance = new ContextController();
    }
    return _instance;
}

ContextController::ContextController() {

}

void ContextController::setCurrent(int current) {
    _current = current;
}

void ContextController::setSceneGLFunctions(QOpenGLFunctions* f, SceneGLView* scene) {
    _GLFunctions[0] = f;
    _GLWidgets[0] = (QOpenGLWidget*)scene;
}

void ContextController::setGameGLFunctions(QOpenGLFunctions* f, GameGLView* game) {
    _GLFunctions[1] = f;
    _GLWidgets[1] = (QOpenGLWidget*)game;
}

QOpenGLFunctions* ContextController::getCurrentContext() {
    _GLWidgets[_current]->makeCurrent();
    return _GLFunctions[_current];
}
