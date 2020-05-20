#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "../game/Transform.h"
#include "lighting/DirectionalLight.h"

class Material {
public:
    Material(Shader* shader, Texture* texture);

    void bind(const Transform&, const Camera&, DirectionalLight light);
private:
    Shader* _shader;
    //TODO: make multiple textures applicable
    Texture* _texture;
};


#endif //GAME_ENGINE_MATERIAL_H
