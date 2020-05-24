
#include <cassert>
#include <iostream>
#include "../../include/engine/graphics/Texture.h"
#include "../../include/engine/game/ContextController.h"

std::map<unsigned int, Texture*> TextureManager::_loadedTextures;

Texture::Texture(const std::string& texturePath) {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    cv::Mat img = cv::imread(texturePath, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

    if (img.data == NULL)
        std::cerr << "Texture loading failed" << std::endl;
    unsigned char* data = img.data;
    img.rows;
    img.cols;

    f->glGenTextures(1, &_texture);
    f->glBindTexture(GL_TEXTURE_2D, _texture);

    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    f->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.rows, img.cols, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture() {
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    f->glDeleteTextures(1, &_texture);
}


void Texture::bind(unsigned int unit) const{
    QOpenGLFunctions* f = ContextController::instance()->getCurrentContext();
    assert(unit >= 0 && unit <= 31);
    f->glActiveTexture(GL_TEXTURE0 + unit);
    f->glBindTexture(GL_TEXTURE_2D, _texture);
}

Texture *Texture::createTexture(const std::string &filePath) {
    unsigned int id;
    if (TextureManager::requestTextureID(filePath, id)) {
        Texture* newTexture = new Texture(filePath);
        TextureManager::addTexture(newTexture, id);
        return newTexture;
    }
    return TextureManager::getTexture(id);
}

void TextureManager::addTexture(Texture *texture, unsigned int id) {
    _loadedTextures[id] = texture;
}

bool TextureManager::requestTextureID(const std::string &filePath, unsigned int& id) {
    id = std::hash<std::string>()(filePath);
    if (_loadedTextures.find(id) == _loadedTextures.end()) {
        return true;
    }
    return false;
}

Texture *TextureManager::getTexture(unsigned int id) {
    return _loadedTextures[id];
}
