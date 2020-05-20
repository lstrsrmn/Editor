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
