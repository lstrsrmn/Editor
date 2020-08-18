#include "../../include/engine/game/Transform.h"
#include "../../include/engine/game/GameObject.h"

void Transform::serializeToJSON(nlohmann::json &object) {
    object["transform"]["pos"] = {_pos.x, _pos.y, _pos.z};
    object["transform"]["rot"] = {_rot.x, _rot.y, _rot.z};
    object["transform"]["scale"] = {_scale.x, _scale.y, _scale.z};
    if (parent) {
        object["transform"]["parentID"] = parent->_object->getSceneObjectID();
    }
}

Transform& Transform::deserializeFromJSON(nlohmann::json &object, GameObject *gameObject) {
    Transform* transform = new Transform(gameObject,
                     glm::vec3(object["transform"]["pos"][0], object["transform"]["pos"][1],object["transform"]["pos"][2]),
                     glm::vec3(object["transform"]["rot"][0], object["transform"]["rot"][1],object["transform"]["rot"][2]),
                     glm::vec3(object["transform"]["scale"][0], object["transform"]["scale"][1],object["transform"]["scale"][2]));
    return *transform;
}

Transform *Transform::getParent() const {
    return parent;
}

void Transform::setParent(Transform *p) {
    if (parent) {
        parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
    }
    parent = p;
    if (parent) {
        parent->children.push_back(this);
    }
}

const std::vector<Transform *> &Transform::getChildren() const {
    return children;
}
