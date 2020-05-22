//
// Created by lstrsrmn on 08/05/2020.
//

#include <QtCore/QString>
#include "../../include/engine/game/GameObject.h"

GameObject::GameObject() {
    _transform = Transform();
}

void GameObject::update() {
    for (Component* component : _components) {
        component->update();
    }
}

Transform &GameObject::getTransform() {
    return _transform;
}

void GameObject::addComponent(Component *component) {
    _components.push_back(component);
    component->setGameObject(this);
}

void GameObject::setScene(Scene *scene) {
    _scene = scene;
}

Scene *GameObject::getScene() const {
    return _scene;
}

const QString &GameObject::getName() const {
    return _name;
}

void GameObject::setName(const QString &name) {
    _name = name;
}

const std::vector<Component *> GameObject::getComponents() const{
    return _components;
}
