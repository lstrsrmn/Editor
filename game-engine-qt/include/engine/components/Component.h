#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

#include "../game/Transform.h"
#include <string>

template<typename T>
struct ComponentInfo {
    static std::string componentName() {return "NO NAME";}
};

#define ENGINE_COMPONENT(type) \
template<> \
struct ComponentInfo<type> { \
    static std::string componentName() {return #type;} \
};

#define SUBSCRIBE_COMPONENT(type) \
public: \
std::string componentName() override {return #type;} \
private:

class GameObject;

class Component {
public:
    virtual void update() {};

    virtual void setGameObject(GameObject *gameObject);

    virtual GameObject* getGameObject();

    virtual std::string componentName();

protected:
    GameObject* _gameObject;
private:

};


#endif //GAME_ENGINE_COMPONENT_H
