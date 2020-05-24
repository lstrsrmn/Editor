#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include <QtOpenGL>
#include <opencv2/opencv.hpp>
#include <map>
#include "../game/Game.h"

class Texture {
public:
    static Texture* createTexture(const std::string&);

    void bind(unsigned int) const;
    virtual ~Texture();
    std::string name;
private:
    Texture(const std::string&);
    Texture(const Texture& other) = default;
    unsigned int _id;
    GLuint _texture;
};

class TextureManager {
public:
    static bool requestTextureID(const std::string&, unsigned int&);
    static void addTexture(Texture*, unsigned int);
    static Texture* getTexture(unsigned int);
private:
    static std::map<unsigned int, Texture*> _loadedTextures;
};

#endif //GAME_ENGINE_TEXTURE_H
