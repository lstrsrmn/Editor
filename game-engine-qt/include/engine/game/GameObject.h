//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_GAMEOBJECT_H
#define GAME_ENGINE_GAMEOBJECT_H

#include <vector>
#include "../components/Component.h"
#include "Transform.h"

class Scene;

class GameObject {
public:
    GameObject();
    void update();
    void addComponent(Component*);
    void setScene(Scene*);
    Scene* getScene() const;
    Transform& getTransform();

    const QString &getName() const;

    void setName(const QString &name);

private:
    QString _name;
    std::vector<Component*> _components;
    Transform _transform;
    Scene* _scene;
};


#endif //GAME_ENGINE_GAMEOBJECT_H
