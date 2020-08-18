#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "../components/MeshRenderer.h"
#include "../game/Transform.h"
#include "../core/AssetManager.h"

class Texture;
class Shader;

class Material : public Asset {
    ASSET(Material)
public:
    static Material* createMaterial(const std::string&, const std::string&, Shader*, Texture*);
    static Material* loadMaterial(const std::string&);
    void bind(Transform&, const Camera&, DirectionalLight* light);
    Texture* _texture;
    Shader* _shader;
private:
    Material(const std::string&, unsigned int);
    //TODO: make multiple textures applicable
};


#endif //GAME_ENGINE_MATERIAL_H
