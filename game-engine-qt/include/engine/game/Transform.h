#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

class Transform {
public:
    Transform(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(),
              const glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0)) :
            _pos(pos),
            _rot(rot),
            _scale(scale) {}

    inline glm::mat4 getModel() const {
        glm::mat4 posMatrix = glm::translate(_pos);
        glm::mat4 rotXMatrix = glm::rotate(_rot.x, glm::vec3(1, 0, 0));
        glm::mat4 rotYMatrix = glm::rotate(_rot.y, glm::vec3(0, 1, 0));
        glm::mat4 rotZMatrix = glm::rotate(_rot.z, glm::vec3(0, 0, 1));
        glm::mat4 scaleMatrix = glm::scale(_scale);
//        glm::vec3 eulerAngles(_pos);
//        glm::quat myQuaternion;
//        myQuaternion = glm::quat(eulerAngles);
//        glm::mat4 rotMatrix = glm::toMat4(myQuaternion);

        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline glm::vec3 &getPos() { return _pos; }

    inline glm::vec3 &getRot() { return _rot; }

    inline glm::vec3 &getScale() { return _scale; }

    inline void setPos(const glm::vec3 &pos) { _pos = pos; }

    inline void setRot(const glm::vec3 &rot) { _rot = rot; }

    inline void setScale(const glm::vec3 &scale) { _scale = scale; }

private:
    glm::vec3 _pos;
    glm::vec3 _rot;
    glm::vec3 _scale;
};


#endif //GAME_ENGINE_TRANSFORM_H
