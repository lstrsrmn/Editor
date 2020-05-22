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
    _sceneCamera->moveBy(movement);
}

void SceneView::orbit(glm::vec2 delta) {
    _sceneCamera->moveBy(-_focus);
    glm::vec3 _pos = _sceneCamera->getPosition();
    float r = glm::length(_pos);
    const glm::vec2 factor = {0.005, 0.005};
    float phi = delta.x * factor.x + atan2(_pos.z, _pos.x);
    float theta = clamp(-delta.y * factor.y + acos(_pos.y / r), 0.01f, M_PIf32 - 0.01f);
    float cosPhi = cos(phi);
    float sinPhi = sin(phi);
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    _sceneCamera->moveTo({r * sinTheta * cosPhi, r * cosTheta, r * sinTheta * sinPhi});
    _sceneCamera->moveBy(_focus);
    _sceneCamera->lookAt(_focus);
}

void SceneView::zoom(float zoomAmount) {
    glm::vec3 pos = _sceneCamera->getPosition() - _focus;
    const float factor = 0.1;
    pos = pos * (exp(zoomAmount * factor));
    _sceneCamera->moveTo(pos + _focus);
}

