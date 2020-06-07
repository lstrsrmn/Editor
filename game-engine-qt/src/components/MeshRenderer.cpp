
#include "../../include/engine/components/MeshRenderer.h"
#include "../../include/engine/game/GameObject.h"

//INIT_COMPONENT(MeshRenderer)
std::map<std::string, Material*> EditorView<MeshRenderer>::materialChoice;

MeshRenderer::MeshRenderer(Material* material, ModelMeshData meshes) {
    _material = material;
    _meshes = meshes;
}


void MeshRenderer::render(const Camera& camera, const DirectionalLight& directionalLight) {
    _material->bind(_gameObject->getTransform(), camera, directionalLight);
    for (unsigned int i = 0; i < _meshes.numMeshes; i++) {
        _meshes.meshes[i]->draw();
    }
}

void MeshRenderer::serializeToJSON(nlohmann::json& object) {
    object["meshRenderer"]["materialID"] = _material->getID();
    object["meshRenderer"]["modelFilePath"] = _meshes.filePath;
}

MeshRenderer *MeshRenderer::deserializeFromJSON(nlohmann::json &object) {
    ModelMeshData meshes = loadModel(object["modelFilePath"]);
    Material* material = AssetManager<Material>::getAsset(object["materialID"]);
    return new MeshRenderer(material, meshes);
}

void MeshRenderer::updateMaterial(const QString &materialName) {
    _material = EditorView<MeshRenderer>::materialChoice[materialName.toStdString()];
}

void EditorView<MeshRenderer>::displayEditorView(MeshRenderer *object, QFormLayout *layout) {
    materialChoice.clear();
    for (std::pair<unsigned int, Material*> materialPair : AssetManager<Material>::getLoadedAssets()) {
        materialChoice[materialPair.second->name] = materialPair.second;
    }
    CallbackListener* materialListener = new CallbackListener(CallbackListener::createCallback(object, &MeshRenderer::updateMaterial));
    EditorFunctions::label(layout, "Material");
    EditorFunctions::dropdownInput(layout, materialListener, materialChoice);
}