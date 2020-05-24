#include "../../include/engine/graphics/Material.h"

Material::Material(Shader* shader, Texture* texture) {
    _shader = shader;
    _texture = texture;
}

void Material::bind(const Transform& transform, const Camera& camera, DirectionalLight light) {
    _shader->bind();
    _texture->bind(0);
    _shader->update(transform, camera, light, glm::vec3(0.11, 0.11, 0.07));
}
