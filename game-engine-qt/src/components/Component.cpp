
#include "../../include/engine/components/Component.h"

std::map<unsigned int, Component*> ComponentFactory::_defaults;

void Component::setGameObject(GameObject *gameObject){
    _gameObject = gameObject;
}

GameObject *Component::getGameObject() {
    return _gameObject;
}

std::string Component::componentName() {
    return "Component";
}

Component::~Component() {

}

Component *ComponentFactory::createComponent(unsigned int ID) {
    return _defaults[ID]->clone();
}

