
#include "../../include/engine/components/Renderer.h"

void Renderer::setGameObject(GameObject *gameObject) {
    Component::setGameObject(gameObject);
    _gameObject->getScene()->addRenderer(this);
}

Renderer::~Renderer() {
    Scene* scene = _gameObject->getScene();
    scene->deleteRenderer(this);
}
