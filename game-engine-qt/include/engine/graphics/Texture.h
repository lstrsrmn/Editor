#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include <QtOpenGL>
#include <opencv2/opencv.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include "Material.h"
#include "../core/AssetManager.h"

// creates texture as an asset through the ASSET macro
class Texture: public Asset {
    ASSET(Texture)
public:
    // static constructor
    static Texture* createTexture(const std::string&, const std::filesystem::path&);
    void bind(unsigned int) const;
    virtual ~Texture();
private:
    // private constructor
    Texture(const std::filesystem::path&, unsigned int);
    GLuint _texture;
};

//ASSET_MAP(Texture)

#endif //GAME_ENGINE_TEXTURE_H
