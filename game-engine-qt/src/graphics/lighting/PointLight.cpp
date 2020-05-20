//
// Created by lstrsrmn on 08/05/2020.
//

#include "../../../include/engine/graphics/lighting/PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 colour, float intensity) {
    _pos = position;
    _colour = colour;
    _intensity = intensity;
}
