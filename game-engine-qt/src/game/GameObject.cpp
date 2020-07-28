//
// Created by lstrsrmn on 08/05/2020.
//

#include <QtCore/QString>
#include <iostream>
#include "../../include/engine/game/GameObject.h"
#include "../../include/engine/components/MeshRenderer.h"

class Scene;

GameObject::GameObject() {
    _transform = Transform(this);
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

GameObject::~GameObject() {
    _scene->deleteObject(this);
    while (!_components.empty()) {
        Component* component = _components[0];
        _components.erase(_components.begin());
        delete component;
    }
}

void GameObject::serializeToJSON(nlohmann::json& scene) {
    _transform.serializeToJSON(scene[_name.toStdString()]);
    for (Component* component: _components) {
        component->serializeToJSON(scene[_name.toStdString()]["components"]);
    }
}

GameObject* GameObject::deserializeFromJSON(nlohmann::json& objectJSON,const std::string& name, Scene* scene) {
    GameObject* object = new GameObject;
    object->_transform = Transform::deserializeFromJSON(objectJSON, object);
    object->_scene = scene;
    object->_name = QString(name.c_str());
    for (nlohmann::json::iterator it = objectJSON["components"].begin(); it != objectJSON["components"].end(); it++) {
        if (it.key() == "meshRenderer") {
            object->addComponent(MeshRenderer::deserializeFromJSON(it.value()));
            continue;
        }
        //TODO : other components
    }
    return object;
}
