#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include <QtOpenGL>
#include <opencv2/opencv.hpp>
#include "../game/Game.h"

class Texture {
public:
    Texture(const std::string&, const std::string& = "res/textures/");

    void bind(unsigned int) const;

    virtual ~Texture();

private:
    Texture(const Texture& other) = default;

    GLuint _texture;
};



#endif //GAME_ENGINE_TEXTURE_H
