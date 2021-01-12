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

class GameObject;

class Transform {
    // give editorview access to all private methods and variables
    friend class EditorView<Transform>;

public:
    Transform(GameObject *object, const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(),
              const glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0)) :
            _pos(pos),
            _rot(rot),
            _scale(scale) {
        _object = object;
    }

    inline glm::mat4 getModel() {
        // optimised by only updating the matrix if the variables has changed
        if (changed) {
            glm::mat4 posMatrix = glm::translate(_pos);
            glm::mat4 scaleMatrix = glm::scale(_scale);
            glm::mat4 rotMatrix = glm::toMat4(glm::quat(_rot * (M_PIf32 / 180.0f)));
            modelMatrix = posMatrix * rotMatrix * scaleMatrix;
            changed = false;
        }

        if (parent) {
            return parent->getModel() * modelMatrix;
        }

        return modelMatrix;
    }

    void serializeToJSON(nlohmann::json &object);

    static Transform& deserializeFromJSON(nlohmann::json &object, GameObject *gameObject);

    inline GameObject *getObject() const {
        return _object;
    }

    const glm::vec3 &getPos() const {
        return _pos;
    }

    void setPos(const glm::vec3 &pos) {
        _pos = pos;
        changed = true;
    }

    const glm::vec3 &getRot() const {
        return _rot;
    }

    void setRot(const glm::vec3 &rot) {
        _rot = rot;
        changed = true;
    }

    const glm::vec3 &getScale() const {
        return _scale;
    }

    void setScale(const glm::vec3 &scale) {
        _scale = scale;
        changed = true;
    }

    Transform *getParent() const;

    void setParent(Transform *parent);

    const std::vector<Transform *> &getChildren() const;

private:
    bool changed = true;
    glm::mat4 modelMatrix;
    glm::vec3 _pos;
    glm::vec3 _rot;
    glm::vec3 _scale;
    GameObject *_object = nullptr;
    std::vector<Transform*> children;
    Transform *parent = nullptr;
};

// allows transforms to be editted in the UI, where position rotation and scale can be editted
CUSTOM_EDITOR(Transform)
{
    DISPLAY_EDITOR_VIEW(Transform) {
        EditorFunctions::label(layout, "Position");
        EditorFunctions::floatInput(layout, "x: ", [object](float val) {
            object->_pos.x = val;
            object->changed = true;
        }, object->_pos.x);
        EditorFunctions::floatInput(layout, "y: ", [object](float val) {
            object->_pos.y = val;
            object->changed = true;
        }, object->_pos.y);
        EditorFunctions::floatInput(layout, "z: ", [object](float val) {
            object->_pos.z = val;
            object->changed = true;
        }, object->_pos.z);

        EditorFunctions::label(layout, "Rotation");
        EditorFunctions::floatInput(layout, "x: ", [object](float val) {
            object->_rot.x = val;
            object->changed = true;
        }, object->_rot.x);
        EditorFunctions::floatInput(layout, "y: ", [object](float val) {
            object->_rot.y = val;
            object->changed = true;
        }, object->_rot.y);
        EditorFunctions::floatInput(layout, "z: ", [object](float val) {
            object->_rot.z = val;
            object->changed = true;
        }, object->_rot.z);

        EditorFunctions::label(layout, "Scale");
        EditorFunctions::floatInput(layout, "x: ", [object](float val) {
            object->_scale.x = val;
            object->changed = true;
        }, object->_scale.x);
        EditorFunctions::floatInput(layout, "y: ", [object](float val) {
            object->_scale.y = val;
            object->changed = true;
        }, object->_scale.y);
        EditorFunctions::floatInput(layout, "z: ", [object](float val) {
            object->_scale.z = val;
            object->changed = true;
        }, object->_scale.z);
    }
};

#endif //GAME_ENGINE_TRANSFORM_H
