#include <cstdio>
#include "../../include/engine/game/Game.h"

Game *Game::_instance = nullptr;

Game *Game::instance() {
    if (_instance == nullptr) {
        _instance = new Game();
    }
    return _instance;
}

void Game::addScene(Scene *scene) {
    if (_scenes[scene->getId()] == nullptr)
        _scenes[scene->getId()] = scene;
}

void Game::setActive(unsigned int sceneID) {
    if (_scenes[sceneID] != nullptr)
        _activeScene = sceneID;
    //TODO:no scene found
}

Scene *Game::activeScene() {
    return _scenes[_activeScene];
}

float Game::getAR() const {
    return _AR;
}

GameErrorCode Game::run() {
    update();
    return SUCCESS;
}

Game::Game() {

}

void Game::update() {
    _scenes[_activeScene]->update();
}

QOpenGLFunctions *Game::getGlFunctions() const {
    return _glFunctions;
}

void Game::setGlFunctions(QOpenGLFunctions *glFunctions) {
    Game::_glFunctions = glFunctions;
}

void Game::setAR(float AR) {
    _scenes[_activeScene]->setAR(AR);
    _AR = AR;
}
