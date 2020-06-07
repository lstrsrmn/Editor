//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_MESHRENDERER_H
#define GAME_ENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "../graphics/Material.h"
#include "../graphics/Mesh.h"
#include "../graphics/ModelImporter.h"
#include "../editor/EditorView.h"

class MeshRenderer;
//void MeshRenderer::updateMaterial(const QString&);

CUSTOM_EDITOR(MeshRenderer) {
    static void displayEditorView(MeshRenderer *object, QFormLayout *layout);
    static std::map<std::string, Material*> materialChoice;
};

class MeshRenderer : public Renderer {
    SUBSCRIBE_COMPONENT(MeshRenderer)
public:
    MeshRenderer(Material*, ModelMeshData);
    void render(const Camera&, const DirectionalLight&) override;
    Material* _material;
    ModelMeshData _meshes{};
    void updateMaterial(const QString&);
    void serializeToJSON(nlohmann::json&) override;
    static MeshRenderer* deserializeFromJSON(nlohmann::json&);

    // TODO: vector of materials instead of 1
};



#endif //GAME_ENGINE_MESHRENDERER_H
