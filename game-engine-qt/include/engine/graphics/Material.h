#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "../components/MeshRenderer.h"
#include "../game/Transform.h"
#include "../core/AssetManager.h"

// Partially defines classes so they can be used as types
class Texture;
class Shader;

// defines material, then defines material as an asset using the ASSET macro
class Material : public Asset {
    ASSET(Material)
public:
    // defines static constructors for creating a new material and loading a prexisting material
    static Material* createMaterial(const std::string&, const std::string&, Shader*, Texture*);
    static Material* loadMaterial(const std::string&);
    // defines the bind function
    void bind(Transform&, const Camera&, DirectionalLight* light);
    Texture* _texture;
    Shader* _shader;
private:
    // private constructor
    Material(const std::string&, unsigned int);
    //TODO: make multiple textures applicable
};


#endif //GAME_ENGINE_MATERIAL_H
