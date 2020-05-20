#include "../../include/engine/graphics/Camera.h"
#include "../../include/engine/game/ContextController.h"
Camera::Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar) {
    _position = pos;
    _fov = fov;
    _zNear = zNear;
    _zFar = zFar;
    _forward = glm::vec3(0, 0, 1);
    _up = glm::vec3(0, 1, 0);
    setAR(aspect);
}

glm::mat4 Camera::getViewProjection() const {
    return _perspective * glm::lookAt(_position, _position + _forward, _up);
}

void Camera::moveBy(glm::vec3 movement) {
    _position += movement;
}

void Camera::clear(float r, float g, float b, float a) {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    f->glClearColor(r, g, b, a);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::rotateBy(float x, float y, float z) {
//    glm::mat4 rotXMatrix = glm::rotate(x, glm::vec3(1, 0, 0));
//    glm::mat4 rotYMatrix = glm::rotate(y, glm::vec3(0, 1, 0));
//    glm::mat4 rotZMatrix = glm::rotate(z, glm::vec3(0, 0, 1));
//
//    glm::mat4 rotMatrix = rotZMatrix * rotXMatrix * rotYMatrix;

//    _up = rotMatrix * glm::vec4(_up, 1);
//    _forward = rotMatrix * glm::vec4(_forward, 1);

    glm::vec3 eulerAngles(x, y, z);
    glm::quat myQuaternion;
    myQuaternion = glm::quat(eulerAngles);
    glm::mat4 rotMatrix = glm::toMat4(myQuaternion);

    _up = rotMatrix * glm::vec4(_up, 1);
    _forward = rotMatrix * glm::vec4(_forward, 1);
}

void Camera::moveTo(glm::vec3 pos){
    _position = pos;
}

const glm::vec3 &Camera::getPosition() const {
    return _position;
}

void Camera::setAR(float aspect) {
    _perspective = glm::perspective(_fov, aspect, _zNear, _zFar);
}

glm::vec3 Camera::getRight() const {
    return glm::cross(_up, _forward);
}

const glm::vec3 &Camera::getForward() const {
    return _forward;
}

void Camera::setForward(const glm::vec3 &forward) {
    _forward = forward;
}

const glm::vec3 &Camera::getUp() const {
    return _up;
}

void Camera::setUp(const glm::vec3 &up) {
    _up = up;
}
