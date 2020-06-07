#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

#include "../game/Transform.h"

#include <string>
#include <nlohmann/json.hpp>

template<typename T>
struct ComponentInfo {
    static std::string componentName() {return "NO NAME";}
};

#define ENGINE_COMPONENT(type) \
template<> \
struct ComponentInfo<type> { \
    static std::string componentName() {return #type;} \
};

#define INIT_COMPONENT(type) \
static type* componentFactoryDefault_##type = ComponentFactory::addComponentDefault<type>();

#define SUBSCRIBE_COMPONENT(type) \
public: \
friend struct ComponentFactory; \
inline std::string componentName() override {return #type;} \
static inline unsigned int getID() { \
    const unsigned int ID = std::hash<std::string>()(#type); \
    return ID; \
} \
inline type* clone() override { \
return new type(); \
} \
void showInspector(QFormLayout* layout) override { \
EditorView<type>::displayEditorView(this, layout); \
} \
private: \
type() = default;

class GameObject;

struct ComponentFactory;

class Component {
public:
    friend struct ComponentFactory;
    virtual void update() {};

    virtual void setGameObject(GameObject *gameObject);

    virtual GameObject* getGameObject();

    virtual std::string componentName();

    virtual ~Component();

    virtual void serializeToJSON(nlohmann::json&) = 0;

    virtual Component* clone() = 0;

    virtual void showInspector(QFormLayout* layout) = 0;

    GameObject* _gameObject;
private:

};

struct ComponentFactory {
    static Component* createComponent(unsigned int);
    template<typename T>
    static T* addComponentDefault();

private:
    static std::map<unsigned int, Component*> _defaults;
};


template<typename T>
T* ComponentFactory::addComponentDefault() {
    T* defaultT = new T();
    _defaults[T::getID()] = defaultT;
    return defaultT;
}

#endif //GAME_ENGINE_COMPONENT_H
