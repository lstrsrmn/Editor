#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QtOpenGL>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../editor/EditorView.h"
//#include "../game/Game.h"

class Scene;

class Camera {
public:

    Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar, glm::vec3 = {0.3, 0.11, 0.11});

    glm::mat4 getViewProjection() const;

    void moveBy(glm::vec3 movement);

    glm::vec3 getRight() const;

    const glm::vec3 &getForward() const;

    void lookAt(glm::vec3);

    void setForward(const glm::vec3 &forward);

    const glm::vec3 &getUp() const;

    void setUp(const glm::vec3 &up);

    void clear(float r, float g, float b, float a);

    void rotateBy(float x, float y, float z);

    void moveTo(glm::vec3 pos);

    const glm::vec3 &getPosition() const;

    void setAR(float);

    void serializeToJSON(nlohmann::json&);

    static Camera* deserializeFromJSON(nlohmann::json&);

    glm::vec3 ambient, _position;
    Scene* _scene;

private:
    float _fov, _zNear, _zFar;
    glm::mat4 _perspective;
    glm::vec3 _forward, _up;
};

CUSTOM_EDITOR(Camera) {
    DISPLAY_EDITOR_VIEW(Camera) {
        FloatEventHandler* xPosInput = new FloatEventHandler(&object->_position.x);
        FloatEventHandler* yPosInput = new FloatEventHandler(&object->_position.y);
        FloatEventHandler* zPosInput = new FloatEventHandler(&object->_position.z);
        FloatEventHandler* xAmbientInput = new FloatEventHandler(&object->ambient.x);
        FloatEventHandler* yAmbientInput = new FloatEventHandler(&object->ambient.y);
        FloatEventHandler* zAmbientInput = new FloatEventHandler(&object->ambient.z);
        ButtonCallbackHandler* buttonCallbackHandler = new ButtonCallbackHandler(ButtonCallbackHandler::createCallback(object->_scene, Scene::updateMaterials));
        EditorFunctions::label(layout, "Position");
        EditorFunctions::floatInput(layout, "x: ", xPosInput, std::to_string(object->_position.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yPosInput, std::to_string(object->_position.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zPosInput, std::to_string(object->_position.z).c_str());
        EditorFunctions::label(layout, "Ambient");
        EditorFunctions::floatInput(layout, "x: ", xAmbientInput, std::to_string(object->ambient.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yAmbientInput, std::to_string(object->ambient.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zAmbientInput, std::to_string(object->ambient.z).c_str());
        EditorFunctions::buttonInput(layout, "Update", buttonCallbackHandler);
    }
};

#endif //GAME_ENGINE_CAMERA_H
