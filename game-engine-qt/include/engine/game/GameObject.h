//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_GAMEOBJECT_H
#define GAME_ENGINE_GAMEOBJECT_H

#include <vector>
#include <nlohmann/json.hpp>
#include "Scene.h"
#include "Transform.h"

class Component;

class GameObject {
public:
    // constructor
    GameObject();
    void update();
    void addComponent(Component*);
    void setScene(Scene*, unsigned int);
    Scene* getScene() const;
    Transform& getTransform();
    const std::vector<Component*> getComponents() const;
    const QString &getName() const;
    void serializeToJSON(nlohmann::json&);
    static GameObject* deserializeFromJSON(nlohmann::json&, const std::string&, Scene*);
    void setName(const QString &name);
    void setParent(GameObject*);

    unsigned int getSceneObjectID() const;

    ~GameObject();

private:
    QString _name;
    std::vector<Component*> _components;
    Transform _transform;
    Scene* _scene;
    unsigned int sceneObjectID;
};


#endif //GAME_ENGINE_GAMEOBJECT_H
