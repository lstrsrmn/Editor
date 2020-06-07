//
// Created by lstrsrmn on 19/05/2020.
//

#include <iostream>
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
//    if (_GLFunctions[current] == nullptr) {
//        if (current == 0) {
//            sCreateContextFunctions();
//        }
//        else {
//            gCreateContextFunctions();
//        }
//    }
    _current = current;
}

void ContextController::setSceneGL(QOpenGLFunctions *f, QOpenGLWidget* widget) {
    _GLFunctions[0] = f;
    _GLWidgets[0] = widget;
}

void ContextController::setGameGL(QOpenGLFunctions *f, QOpenGLWidget* widget) {
    _GLFunctions[1] = f;
    _GLWidgets[1] = widget;
}

QOpenGLFunctions* ContextController::getCurrentFunctions() {
//    if (!_current)
//        sMakeCurrent();
//    else
//        gMakeCurrent();
    _GLWidgets[_current]->makeCurrent();
//    QOpenGLContext::globalShareContext()->makeCurrent(_GLWidgets[_current]->context()->surface());
    return _GLFunctions[_current];
}

int ContextController::getCurrent() const {
    return _current;
}

QOpenGLContext *ContextController::getSceneContext() {
    return _GLWidgets[0]->context();
}

//void ContextController::setSceneGLCallbacks(std::function<void()> makeCurrent, std::function<void()> createContextFunctions) {
//    sMakeCurrent = makeCurrent;
//    sCreateContextFunctions = createContextFunctions;
//}
//
//void ContextController::setGameGLCallbacks(std::function<void()> makeCurrent, std::function<void()> createContextFunctions) {
//    gMakeCurrent = makeCurrent;
//    gCreateContextFunctions = createContextFunctions;
//}
