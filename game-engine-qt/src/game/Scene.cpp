
#include <iostream>
#include "../../include/engine/game/Scene.h"

SceneManager *SceneManager::_instance = nullptr;

Scene::Scene(Camera *camera, DirectionalLight light) {
    _camera = camera;
    _directionalLight = light;
    _id = SceneManager::instance()->addScene(this);
}

void Scene::update() {
    for (GameObject *obj : _gameObjects) {
        obj->update();
    }

    //TODO: physics

    draw();
}

GameObject *Scene::createGameObject() {
    GameObject *gameObject = new GameObject();
    _gameObjects.push_back(gameObject);
    gameObject->setScene(this);
    return gameObject;
}

void Scene::addRenderer(Renderer *renderer) {
    _renderers.push_back(renderer);
}

unsigned int Scene::getId() const {
    return _id;
}

void Scene::setAR(float AR) {
    _camera->setAR(AR);
}

const QString &Scene::getName() const {
    return _name;
}

void Scene::setName(const QString &name) {
    _name = name;
}

void Scene::draw() {
    _camera->clear(0.0f, 0.15f, 0.3f, 1.0f);
    for (Renderer *renderer : _renderers) {
        renderer->render(*_camera, _directionalLight);
    }
}

void Scene::draw(Camera* camera) {
    camera->clear(0.0f, 0.15f, 0.3f, 1.0f);
    for (Renderer *renderer : _renderers) {
        renderer->render(*camera, _directionalLight);
    }
}

std::vector<GameObject*> Scene::getObjects() {
    return _gameObjects;
}

void Scene::deleteObject(GameObject* object) {
    for (unsigned int i = 0; i < _gameObjects.size(); i++) {
        if (_gameObjects[i] == object) {
            _gameObjects.erase(_gameObjects.begin() + i);
        }
    }
}

void Scene::deleteRenderer(Renderer* renderer) {
    for (unsigned int i = 0; i < _renderers.size(); i++) {
        if (_renderers[i] == renderer) {
            _renderers.erase(_renderers.begin() + i);
        }
    }
}

SceneManager *SceneManager::instance() {
    if (_instance == nullptr) {
        _instance = new SceneManager();
    }

    return _instance;
}

unsigned int SceneManager::addScene(Scene *scene) {
    _scenes.push_back(scene);
    return _numScenes++;
}
