#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <math.h>
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
//        glm::mat4 rotXMatrix = glm::rotate(_rot.x, glm::vec3(1, 0, 0));
//        glm::mat4 rotYMatrix = glm::rotate(_rot.y, glm::vec3(0, 1, 0));
//        glm::mat4 rotZMatrix = glm::rotate(_rot.z, glm::vec3(0, 0, 1));
//        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
        glm::mat4 scaleMatrix = glm::scale(scale);
        glm::mat4 rotMatrix = glm::toMat4(glm::quat(rot * (M_PIf32 / 180.0f)));

        return posMatrix * rotMatrix * scaleMatrix;
    }
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

private:
};

CUSTOM_EDITOR(Transform) {
    DISPLAY_EDITOR_VIEW(Transform) {
        FloatEventHandler* xInput = new FloatEventHandler(&object->pos.x);
        FloatEventHandler* yInput = new FloatEventHandler(&object->pos.y);
        FloatEventHandler* zInput = new FloatEventHandler(&object->pos.z);
        EditorFunctions::floatInput(layout, "x: ", xInput, std::to_string(object->pos.x).c_str());
        EditorFunctions::floatInput(layout, "y: ", yInput, std::to_string(object->pos.y).c_str());
        EditorFunctions::floatInput(layout, "z: ", zInput, std::to_string(object->pos.z).c_str());
    }
};

#endif //GAME_ENGINE_TRANSFORM_H
