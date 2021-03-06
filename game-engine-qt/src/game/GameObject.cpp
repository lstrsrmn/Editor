//
// Created by lstrsrmn on 08/05/2020.
//

#include <QtCore/QString>
#include <iostream>
#include "../../include/engine/game/GameObject.h"
#include "../../include/engine/components/MeshRenderer.h"

class Scene;

GameObject::GameObject() : _transform(this) {
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
    // adds component to game object list of componenents, and set the components game object to this
    if (component) {
        _components.push_back(component);
        component->setGameObject(this);
    }
}

void GameObject::setScene(Scene *scene, unsigned int id) {
    _scene = scene;
    this->sceneObjectID = id;
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
    scene[_name.toStdString()]["sceneObjectID"] = sceneObjectID;
    _transform.serializeToJSON(scene[_name.toStdString()]);
    for (Component* component: _components) {
        component->serializeToJSON(scene[_name.toStdString()]["components"]);
    }
}

GameObject* GameObject::deserializeFromJSON(nlohmann::json& objectJSON,const std::string& name, Scene* scene) {
    GameObject* object = new GameObject;
    object->sceneObjectID = objectJSON["sceneObjectID"];
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

void GameObject::setParent(GameObject *parent) {
    if (parent) {
        _transform.setParent(&parent->_transform);
    }
    else {
        _transform.setParent(nullptr);
    }
}

unsigned int GameObject::getSceneObjectID() const {
    return sceneObjectID;
}
