//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_POINTLIGHT_H
#define GAME_ENGINE_POINTLIGHT_H

#include <glm/glm.hpp>

class PointLight {
public:
    PointLight(glm::vec3 position, glm::vec3 colour = glm::vec3(1, 1, 1), float intensity = 1);
private:
    float _intensity = 1;
    glm::vec3 _pos{};
    glm::vec3 _colour{};
};


#endif //GAME_ENGINE_POINTLIGHT_H
