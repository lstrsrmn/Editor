
#include "../../include/engine/components/MeshRenderer.h"
#include "../../include/engine/graphics/Material.h"

//INIT_COMPONENT(MeshRenderer)
std::map<std::string, Material*> EditorView<MeshRenderer>::materialChoice;

MeshRenderer::MeshRenderer(Material* material, Mesh* mesh) {
    _material = material;
    _mesh = mesh;
}


void MeshRenderer::render(const Camera& camera, DirectionalLight* directionalLight) {
    _material->bind(_gameObject->getTransform(), camera, directionalLight);
    _mesh->draw();
}

void MeshRenderer::serializeToJSON(nlohmann::json& object) {
    object["meshRenderer"]["materialID"] = _material->getID();
    object["meshRenderer"]["meshDataID"] = _mesh->getModelMeshData()->getID();
    object["meshRenderer"]["subMeshID"] = _mesh->getID();
}

MeshRenderer *MeshRenderer::deserializeFromJSON(nlohmann::json &object) {
//    TODO: static model loader for scene assets
    ModelMeshData* meshData = AssetManager<ModelMeshData>::getAsset(object["meshDataID"]);
    Material* material = AssetManager<Material>::getAsset(object["materialID"]);
    Mesh* mesh = meshData->getSubMesh(object["subMeshID"]);
    if (mesh)
        return new MeshRenderer(material, mesh);
    else
        return nullptr;
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