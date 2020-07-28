#ifndef GAME_ENGINE_DIRECTIONALLIGHT_H
#define GAME_ENGINE_DIRECTIONALLIGHT_H

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include "../Shader.h"

class DirectionalLight {
public:
    DirectionalLight(glm::vec3 = glm::vec3(0, 0, 1), glm::vec3 = glm::vec3(1, 1, 1), float = 1.0f);

    const glm::vec3 &getDirection() const;

    void setDirection(const glm::vec3 &direction);

    glm::vec3 getColour() const;

    void setColour(const glm::vec3 &colour);

    void setIntensity(float intensity);

    void serializeToJSON(nlohmann::json&);

    static DirectionalLight* deserializeFromJSON(nlohmann::json&);

private:
    float _intensity = 1.0f;
    glm::vec3 _direction{};
    glm::vec3 _colour{};
};


#endif //GAME_ENGINE_DIRECTIONALLIGHT_H
