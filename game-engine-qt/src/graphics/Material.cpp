#include "../../include/engine/graphics/Material.h"
#include "../../include/engine/graphics/Shader.h"
#include "../../include/engine/graphics/Texture.h"

Material *Material::createMaterial(const std::string &name, const std::string &filePath, Shader *shader, Texture *texture) {
    // creates and wires to properties mat file
    std::ofstream materialMat(filePath + "/" + name + ".mat");
    nlohmann::json material;
    material["texture"] = texture->getID();
    material["shader"] = shader->getID();
    materialMat << material.dump(4) << std::endl;
    // creates a material and assigns properties
    Material* newMaterial = AssetManager<Material>::createAsset(name, filePath + "/" + name + ".mat");
    newMaterial->_shader = shader;
    newMaterial->_texture = texture;
    return newMaterial;
}

void Material::bind(Transform &transform, const Camera &camera, DirectionalLight* light) {
    // binds shader and textures
    _shader->bind();
    _texture->bind(0);
    _shader->update(transform, camera, light);
}

Material::Material(const std::string &filePath, unsigned int id) : Asset(filePath, id) {
    // reads properties from file path
    std::ifstream materialMat(filePath);
    nlohmann::json material;
    materialMat >> material;
    // loads textures and shaders
    Texture* texture = AssetManager<Texture>::getAsset(material["texture"]);
    Shader* shader = AssetManager<Shader>::getAsset(material["shader"]);
    // assigns them locally
    _shader = shader;
    _texture = texture;
}

Material *Material::loadMaterial(const std::string &filePath) {
    // requests material object from asset manager
    return AssetManager<Material>::getAsset(std::hash<std::string>()(filePath));
}
