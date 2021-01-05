#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

// for include tree
#include "../game/Transform.h"
#include "../game/GameObject.h"

// includes such that the program can use the string and json packages
#include <string>
#include <nlohmann/json.hpp>

// defines a template, expecting class type T (not defined yet), this is the default where no type is defined
template<typename T>
struct ComponentInfo {
    static std::string componentName() {return "NO NAME";}
};

// defines a macro function that takes a type and creates a template that overrides the one defined above, this section of code is made to be able to retrieve a components type name
#define ENGINE_COMPONENT(type) \
template<> \
struct ComponentInfo<type> { \
    static std::string componentName() {return #type;} \
};

// when init component macro is called, calls componentFactorys function "addComponentDefault" with this type
#define INIT_COMPONENT(type) \
static type* componentFactoryDefault_##type = ComponentFactory::addComponentDefault<type>();

// macro explination
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
