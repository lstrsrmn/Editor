#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <math.h>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "../editor/EditorView.h"

class Transform {
public:
    Transform(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(),
              const glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0)) :
            pos(pos),
            rot(rot),
            scale(scale) {}

    inline glm::mat4 getModel() const {
        glm::mat4 posMatrix = glm::translate(pos);
        glm::mat4 scaleMatrix = glm::scale(scale);
        glm::mat4 rotMatrix = glm::toMat4(glm::quat(rot * (M_PIf32 / 180.0f)));

        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline void serializeToJSON(nlohmann::json& object) {
        object["transform"]["pos"] = {pos.x, pos.y, pos.z};
        object["transform"]["rot"] = {rot.x, rot.y, rot.z};
        object["transform"]["scale"] = {scale.x, scale.y, scale.z};
    }

    inline static Transform deserializeFromJSON(nlohmann::json& object) {
        return Transform(glm::vec3(object["transform"]["pos"][0], object["transform"]["pos"][1], object["transform"]["pos"][2]),
                glm::vec3(object["transform"]["rot"][0], object["transform"]["rot"][1], object["transform"]["rot"][2]),
                glm::vec3(object["transform"]["scale"][0], object["transform"]["scale"][1], object["transform"]["scale"][2]));
    }

    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

private:
};

CUSTOM_EDITOR(Transform) {
    DISPLAY_EDITOR_VIEW(Transform) {
        FloatEventHandler* xPosInput = new FloatEventHandler(&object->pos.x);
        FloatEventHandler* yPosInput = new FloatEventHandler(&object->pos.y);
        FloatEventHandler* zPosInput = new FloatEventHandler(&object->pos.z);
        FloatEventHandler* xRotInput = new FloatEventHandler(&object->rot.x);
        FloatEventHandler* yRotInput = new FloatEventHandler(&object->rot.y);
        FloatEventHandler* zRotInput = new FloatEventHandler(&object->rot.z);
        FloatEventHandler* xScaleInput = new FloatEventHandler(&object->scale.x);
        FloatEventHandler* yScaleInput = new FloatEventHandler(&object->scale.y);
        FloatEventHandler* zScaleInput = new FloatEventHandler(&object->scale.z);
        EditorFunctions::label(layout, "Position");
        EditorFunctions::floatInput(layout, "x: ", xPosInput, std::to_string(object->pos.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yPosInput, std::to_string(object->pos.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zPosInput, std::to_string(object->pos.z).c_str());
        EditorFunctions::label(layout, "Rotation");
        EditorFunctions::floatInput(layout, "x: ", xRotInput, std::to_string(object->rot.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yRotInput, std::to_string(object->rot.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zRotInput, std::to_string(object->rot.z).c_str());
        EditorFunctions::label(layout, "Scale");
        EditorFunctions::floatInput(layout, "x: ", xScaleInput, std::to_string(object->scale.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yScaleInput, std::to_string(object->scale.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zScaleInput, std::to_string(object->scale.z).c_str());
    }
};

#endif //GAME_ENGINE_TRANSFORM_H
