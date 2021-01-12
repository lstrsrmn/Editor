#include "../../include/engine/game/Game.h"
#include "../../include/engine/game/Scene.h"

Game *Game::_instance = nullptr;

Game *Game::instance() {
    // returns a new game object if one doesnt exist, if one exists returns that making a max of 1 "Game" classes created at any time
    if (_instance == nullptr) {
        _instance = new Game();
    }
    return _instance;
}

void Game::addScene(Scene *scene) {
    // adds a scene to the game
    if (_scenes.empty())
        _scenes[scene->getId()] = scene;
    else if (_scenes[scene->getId()] == nullptr)
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
    // sets AR of all scenes in game
    if (_scenes[_activeScene] != nullptr)
        _scenes[_activeScene]->setAR(AR);
    _AR = AR;
}
