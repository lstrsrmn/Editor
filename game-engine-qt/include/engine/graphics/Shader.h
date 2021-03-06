#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <string>
#include <QtOpenGL>
#include <iostream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "../game/Transform.h"
#include "../core/AssetManager.h"
#include "Material.h"

// forward declaring
class Camera;
class DirectionalLight;

// creates class shader as an asset through the ASSET macro
class Shader : public Asset{
    ASSET(Shader)
public:
    // static constructor for shader
    static Shader* createShader(const std::string&, const std::filesystem::path&, const std::filesystem::path & = "res/shaders/");
//    static Shader* createAsset(const std::string&, const std::string&, const std::string & = "res/shaders/");
    void bind() const;
    
    void update(Transform &transform, const Camera& camera, DirectionalLight* directionalLight);

    virtual ~Shader();

private:
    static const unsigned int NUM_SHADER = 2;
    // private constructor
    Shader(const std::filesystem::path &, unsigned int);

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

//ASSET_MAP(Shader)

#endif //GAME_ENGINE_SHADER_H
