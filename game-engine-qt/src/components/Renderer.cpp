
#include "../../include/engine/components/Renderer.h"
#include "../../include/engine/game/GameObject.h"
#include "../../include/engine/game/Scene.h"

void Renderer::setGameObject(GameObject *gameObject) {
    Component::setGameObject(gameObject);
    _gameObject->getScene()->addRenderer(this);
}
