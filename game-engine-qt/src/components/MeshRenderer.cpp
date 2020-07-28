
#include "../../include/engine/components/MeshRenderer.h"
#include "../../include/engine/graphics/Material.h"

//INIT_COMPONENT(MeshRenderer)
std::map<std::string, Material*> EditorView<MeshRenderer>::materialChoice;

MeshRenderer::MeshRenderer(Material* material, ModelMeshData data) {
    _material = material;
    _meshData = data;
}


void MeshRenderer::render(const Camera& camera, DirectionalLight* directionalLight) {
    _material->bind(_gameObject->getTransform(), camera, directionalLight);
    __render(_meshData.tree);
}

void MeshRenderer::serializeToJSON(nlohmann::json& object) {
    object["meshRenderer"]["materialID"] = _material->getID();
    object["meshRenderer"]["modelFilePath"] = _meshData.filePath;
}

MeshRenderer *MeshRenderer::deserializeFromJSON(nlohmann::json &object) {
//    TODO: static model loader for scene assets
    ModelMeshData meshData = loadModel(object["modelFilePath"]);
    Material* material = AssetManager<Material>::getAsset(object["materialID"]);
    return new MeshRenderer(material, meshData);
}

void MeshRenderer::updateMaterial(const QString &materialName) {
    _material = EditorView<MeshRenderer>::materialChoice[materialName.toStdString()];
}

void MeshRenderer::__render(ModelMeshTree* tree) const{
    for (unsigned int i = 0; i < tree->numMeshes; i++) {
        tree->meshes[i]->draw();
    }
    for (unsigned int i = 0; i < tree->numChildren; i++) {
        __render(tree->children[i]);
    }
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