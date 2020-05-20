//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

#include "../game/Transform.h"

class GameObject;

class Component {
public:
    virtual void update() {};

    virtual void setGameObject(GameObject *gameObject);

protected:
    GameObject* _gameObject;
private:

};


#endif //GAME_ENGINE_COMPONENT_H
