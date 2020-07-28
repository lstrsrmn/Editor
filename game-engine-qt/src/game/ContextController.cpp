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

void ContextController::setGL(QOpenGLFunctions *f, QOpenGLWidget* widget) {
    instance()->_GLFunctions = f;
    instance()->_GLWidget = widget;
}
QOpenGLFunctions* ContextController::getFunctions() {
    instance()->_GLWidget->makeCurrent();
    return instance()->_GLFunctions;
}

QOpenGLContext *ContextController::getContext() {
    return instance()->_GLWidget->context();
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
