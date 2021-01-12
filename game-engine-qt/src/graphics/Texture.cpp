
#include <cassert>
#include <iostream>
#include "../../include/engine/graphics/Texture.h"
//#include "../../include/engine/game/ContextController.h"

Texture::Texture(const std::filesystem::path& texturePath, unsigned int id) : Asset(texturePath, id){
    QOpenGLFunctions* f = Game::instance()->getGlFunctions();
    // loads in the image using opencv
    cv::Mat img = cv::imread(texturePath, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    
    // makes sure the image loaded correctly
    if (img.data == NULL)
        std::cerr << "Texture loading failed" << std::endl;
    unsigned char* data = img.data;

    // runs all nececary opengl functions to create textures
    f->glGenTextures(1, &_texture);
    f->glBindTexture(GL_TEXTURE_2D, _texture);

    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    f->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    f->glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // assigns the image to the opengl texture created above
    f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.rows, img.cols, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
}

Texture::~Texture() {
//    QOpenGLFunctions* f = ContextController::instance()->getCurrentFunctions();
    QOpenGLFunctions* f = Game::instance()->getGlFunctions();
    f->glDeleteTextures(1, &_texture);
}


void Texture::bind(unsigned int unit) const{
//    QOpenGLFunctions* f = ContextController::instance()->getCurrentFunctions();
    QOpenGLFunctions* f = Game::instance()->getGlFunctions();
    assert(unit >= 0 && unit <= 31);
    f->glActiveTexture(GL_TEXTURE0 + unit);
    f->glBindTexture(GL_TEXTURE_2D, _texture);
}

Texture *Texture::createTexture(const std::string &name, const std::filesystem::path &filePath) {
    return AssetManager<Texture>::createAsset(name, filePath);
}
