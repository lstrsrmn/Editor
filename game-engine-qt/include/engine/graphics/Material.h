#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "../game/Transform.h"
#include "lighting/DirectionalLight.h"

class Material : public Asset {
    ASSET(Material)
public:
    static Material* createMaterial(const std::string&, const std::string&, Shader*, Texture*);
    static Material* loadMaterial(const std::string&);
    void bind(const Transform&, const Camera&, DirectionalLight light);
    Texture* getTexture() const;
    Shader* getShader() const;
private:
    Material(const std::string&, unsigned int);
    Texture* _texture;
    Shader* _shader;
    //TODO: make multiple textures applicable
};


#endif //GAME_ENGINE_MATERIAL_H
