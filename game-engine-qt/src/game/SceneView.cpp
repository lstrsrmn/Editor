#include "../../include/engine/game/SceneView.h"

SceneView *SceneView::_instance = nullptr;

SceneView *SceneView::instance() {
    if (_instance == nullptr) {
        _instance = new SceneView();
    }
    return _instance;
}

SceneView::SceneView() {

}

void SceneView::addScene(Scene *scene) {
    if (_scenes[scene->getId()] == nullptr)
        _scenes[scene->getId()] = scene;
}

float SceneView::getAR() const {
    return _AR;
}

void SceneView::setAR(float ar) {
    _AR = ar;
    if (_sceneCamera != nullptr)
        _sceneCamera->setAR(ar);
}

void SceneView::makeCamera() {
    if (_AR != 0 && _sceneCamera == nullptr)
        _sceneCamera = new Camera(glm::vec3(0, 0, 0), 70.0f, _AR, 0.001f, 1000.0f);
}

void SceneView::update() {
    _scenes[_activeScene]->draw(_sceneCamera);
}

void SceneView::setActive(unsigned int sceneID) {
    if (_scenes[sceneID] != nullptr)
        _activeScene = sceneID;
}

QOpenGLFunctions *SceneView::getGlFunctions() const {
    return _glFunctions;
}

void SceneView::setGlFunctions(QOpenGLFunctions *glFunctions) {
    _glFunctions = glFunctions;
}

Camera *SceneView::getCamera() {
    return _sceneCamera;
}

Scene *SceneView::getCurrentScene() {
    return _scenes[_activeScene];
}

void SceneView::pan(glm::vec2 delta) {
    const glm::vec2 factor = {0.005, 0.005};
    glm::vec3 movement = _sceneCamera->getRight() * delta.x * factor.x + _sceneCamera->getUp() * delta.y * factor.y;
    _focus += movement;
    _sceneCamera->moveBy(-movement);
}

void SceneView::orbit(glm::vec2 delta) {
    const glm::vec2 factor = {0.005, 0.005};
    float phi = delta.x * factor.x;
    float theta = delta.y * factor.y;
    float cosPhi = cos(phi);
    float sinPhi = sin(phi);
    glm::vec3 _pos = _sceneCamera->getPosition() - _focus;
    float radius = _pos.length();
    glm::vec3 previousPos = _pos;
    _pos.x = previousPos.x * cosPhi - previousPos.z * sinPhi;
    _pos.z = previousPos.x * sinPhi + previousPos.z * cosPhi;
    _sceneCamera->moveTo(_pos + _focus);
    _sceneCamera->rotateBy(0, -phi, 0);

    glm::vec3 previousUp = _sceneCamera->getUp();
    _sceneCamera->rotateBy(-theta, 0, 0);
    glm::vec3 movementDirection = (previousUp + _sceneCamera->getUp());
    float movementAmount = 2 * radius * sin(theta/2) / movementDirection.length();
    _sceneCamera->moveBy(movementDirection * movementAmount);
}

