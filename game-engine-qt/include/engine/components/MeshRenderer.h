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


class MeshRenderer : public Renderer {
    SUBSCRIBE_COMPONENT(MeshRenderer)
public:
    MeshRenderer(Material*, ModelMeshData);
    void render(const Camera&, const DirectionalLight&) override;
    Material* _material;
    ModelMeshData _meshes{};
    float _random;
    // TODO: vector of materials instead of 1
};
#endif //GAME_ENGINE_MESHRENDERER_H
