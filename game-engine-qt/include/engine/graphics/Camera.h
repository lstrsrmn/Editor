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
#include "../game/Scene.h"
//#include "../game/Game.h"

class Camera {
    friend class EditorView<Camera>;
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

    glm::vec3 ambient, position;
    Scene* _scene;

private:
    float _fov, _zNear, _zFar;
    glm::mat4 _perspective;
    glm::vec3 _forward, _up;
};

CUSTOM_EDITOR(Camera) {
    DISPLAY_EDITOR_VIEW(Camera) {
        EditorFunctions::label(layout, "Position");
        EditorFunctions::floatInput(layout, "x: ", object->position.x);
        EditorFunctions::floatInput(layout, "y: ", object->position.y);
        EditorFunctions::floatInput(layout, "z: ", object->position.z);

        EditorFunctions::label(layout, "Ambient");
        EditorFunctions::floatInput(layout, "r: ", object->ambient.r);
        EditorFunctions::floatInput(layout, "g: ", object->ambient.g);
        EditorFunctions::floatInput(layout, "b: ", object->ambient.b);
    }
};

#endif //GAME_ENGINE_CAMERA_H
