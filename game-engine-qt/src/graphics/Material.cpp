#include "../../include/engine/graphics/Material.h"
#include "../../include/engine/graphics/Shader.h"
#include "../../include/engine/graphics/Texture.h"

Material *Material::createMaterial(const std::string &name, const std::string &filePath, Shader *shader, Texture *texture) {
    std::ofstream materialMat(filePath + "/" + name + ".mat");
    nlohmann::json material;
    material["texture"] = texture->getID();
    material["shader"] = shader->getID();
    materialMat << material.dump(4) << std::endl;
    Material* newMaterial = AssetManager<Material>::createAsset(name, filePath + "/" + name + ".mat");
    newMaterial->_shader = shader;
    newMaterial->_texture = texture;
    return newMaterial;
}

void Material::bind(Transform &transform, const Camera &camera, DirectionalLight* light) {
    _shader->bind();
    _texture->bind(0);
    _shader->update(transform, camera, light);
}

Material::Material(const std::string &filePath, unsigned int id) : Asset(filePath, id) {
    std::ifstream materialMat(filePath);
    nlohmann::json material;
    materialMat >> material;
    Texture* texture = AssetManager<Texture>::getAsset(material["texture"]);
    Shader* shader = AssetManager<Shader>::getAsset(material["shader"]);
    _shader = shader;
    _texture = texture;
}

Material *Material::loadMaterial(const std::string &filePath) {
    return AssetManager<Material>::getAsset(std::hash<std::string>()(filePath));
}
