#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <string>
#include <QtOpenGL>
#include <iostream>
#include "../game/Transform.h"
#include "Camera.h"
#include "lighting/DirectionalLight.h"
#include "lighting/PointLight.h"
#include "../game/Game.h"
//#include "../game/ContextController.h"


class Shader {
public:
    Shader(const std::string &, const std::string & = "res/shaders/");

    void bind() const;

    void update(const Transform &transform, const Camera& camera, DirectionalLight directionalLight, glm::vec3 ambient);

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADER = 2;

    Shader(const Shader &other) = default;

    DirectionalLight _lightDirection;
    glm::vec3 _ambient;

    enum {
        TRANSFORM_U,
        NORMAL_MATRIX_U,
        DIRECTIONAL_LIGHT_DIRECTION_U,
        AMBIENT_U,
        DIRECTIONAL_LIGHT_COLOUR_U,

        NUM_UNIFORMS
    };

    GLuint _program;
    GLuint _shaders[NUM_SHADER];
    GLuint _uniforms[NUM_UNIFORMS];
};


#endif //GAME_ENGINE_SHADER_H
