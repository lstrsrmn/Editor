
#include "../../include/engine/components/Component.h"

void Component::setGameObject(GameObject *gameObject){
    _gameObject = gameObject;
}

GameObject *Component::getGameObject() {
    return _gameObject;
}

std::string Component::componentName() {
    return "Component";
}
