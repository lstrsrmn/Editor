//
// Created by lstrsrmn on 08/05/2020.
//

#include "../../../include/engine/graphics/lighting/DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 colour, float intensity) {
    _intensity = intensity;
    _direction = direction;
    _colour = colour;
}

const glm::vec3 &DirectionalLight::getDirection() const {
    return _direction;
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    _direction = direction;
}

glm::vec3 DirectionalLight::getColour() const {
    return _colour * _intensity;
}

void DirectionalLight::setColour(const glm::vec3 &colour) {
    _colour = colour;
}

void DirectionalLight::setIntensity(float intensity) {
    _intensity = intensity;
}

void DirectionalLight::serializeToJSON(nlohmann::json &scene) {
    scene["directionalLight"]["direction"] = {_direction.x, _direction.y, _direction.z};
    scene["directionalLight"]["colour"] = {_colour.r, _colour.g, _colour.b};
    scene["directionalLight"]["intensity"] = _intensity;
}

DirectionalLight DirectionalLight::deserializeFromJSON(nlohmann::json &scene) {
    glm::vec3 direction{scene["directionalLight"]["direction"][0], scene["directionalLight"]["direction"][1], scene["directionalLight"]["direction"][2]};
    glm::vec3 colour{scene["directionalLight"]["colour"][0], scene["directionalLight"]["colour"][1], scene["directionalLight"]["colour"][2]};
    return DirectionalLight(direction, colour, scene["directionalLight"]["intensity"]);
}
