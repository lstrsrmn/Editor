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

void ContextController::setSceneGLFunctions(QOpenGLFunctions* f) {
    _GLFunctions[0] = f;
}

void ContextController::setGameGLFunctions(QOpenGLFunctions* f) {
    _GLFunctions[1] = f;
}

QOpenGLFunctions* ContextController::getCurrentContext() {
    return _GLFunctions[_current];
}
