#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <QtOpenGL>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include "../game/Game.h"

class Camera {
public:
    Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar);

    glm::mat4 getViewProjection() const;

    void moveBy(glm::vec3 movement);

    glm::vec3 getRight() const;

    const glm::vec3 &getForward() const;

    void setForward(const glm::vec3 &forward);

    const glm::vec3 &getUp() const;

    void setUp(const glm::vec3 &up);

    void clear(float r, float g, float b, float a);

    void rotateBy(float x, float y, float z);

    void moveTo(glm::vec3 pos);

    const glm::vec3 &getPosition() const;

    void setAR(float);

private:
    float _fov, _zNear, _zFar;
    glm::mat4 _perspective;
    glm::vec3 _position, _forward, _up;
};


#endif //GAME_ENGINE_CAMERA_H
