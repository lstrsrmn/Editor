#include "../../include/engine/graphics/Camera.h"
#include "../../include/engine/game/ContextController.h"
#include <iostream>
Camera::Camera(glm::vec3 pos, float fov, float aspect, float zNear, float zFar, glm::vec3 amb) {
    _position = pos;
    ambient = amb;
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
    QOpenGLFunctions* f = ContextController::instance()->getCurrentFunctions();
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
    glm::quat qx(cos(x / 2), getRight() * sin(x / 2));
    glm::quat qy(cos(y / 2), getUp() * sin(y / 2));
    glm::quat qz(cos(z / 2), getForward() * sin(z / 2));

    glm::mat4 rotMatrix = glm::toMat4(qz * qx * qy);

    _up = rotMatrix * glm::vec4(_up, 1);
    _forward = rotMatrix * glm::vec4(_forward, 1);
}

void Camera::lookAt(glm::vec3 target) {
    _forward = glm::normalize(target - _position);
    glm::vec3 _right = glm::normalize(glm::vec3(_forward.z, 0, -_forward.x));
    _up = glm::cross(_forward, _right);
//    _up = glm::normalize(glm::vec3(_forward.x, (pow(_forward.x, 2) + pow(_forward.z, 2)) / _forward.y, _forward.z));
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

void Camera::serializeToJSON(nlohmann::json &scene) {
    scene["camera"]["pos"] = {_position.x, _position.y, _position.z};
    scene["camera"]["fov"] = _fov;
    scene["camera"]["clipping"] = {_zNear, _zFar};
    scene["camera"]["ambient"] = {ambient.x, ambient.y, ambient.z};
}

Camera *Camera::deserializeFromJSON(nlohmann::json &scene) {
    glm::vec3 pos{scene["camera"]["pos"][0], scene["camera"]["pos"][1], scene["camera"]["pos"][2]};
    glm::vec3 amb{scene["camera"]["ambient"][0], scene["camera"]["ambient"][1], scene["camera"]["ambient"][2]};
    return new Camera(pos, scene["camera"]["fov"], 70, scene["camera"]["clipping"][0], scene["camera"]["clipping"][1], amb);
}
