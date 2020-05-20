
#include "../../include/engine/components/MeshRenderer.h"
#include "../../include/engine/game/GameObject.h"

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

