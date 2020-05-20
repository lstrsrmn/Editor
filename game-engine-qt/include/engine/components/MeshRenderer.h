//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_MESHRENDERER_H
#define GAME_ENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "../graphics/Material.h"
#include "../graphics/Mesh.h"


class MeshRenderer : public Renderer {
public:
    MeshRenderer(Material*, ModelMeshData);
    void render(const Camera&, const DirectionalLight&) override;
private:
    // TODO: vector of materials instad of 1
    Material* _material;
    ModelMeshData _meshes{};
};


#endif //GAME_ENGINE_MESHRENDERER_H
