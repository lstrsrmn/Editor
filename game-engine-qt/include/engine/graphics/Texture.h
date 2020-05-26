#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include <QtOpenGL>
#include <opencv2/opencv.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include "../game/Game.h"
#include "../core/Asset.h"
#include "../core/AssetManager.h"

class Texture: public Asset {
    ASSET(Texture)
public:
    static Texture* createTexture(const std::string&, const std::string&);
    void bind(unsigned int) const;
    virtual ~Texture();
private:
    Texture(const std::string&, unsigned int);
    GLuint _texture;
};

//ASSET_MAP(Texture)

#endif //GAME_ENGINE_TEXTURE_H
