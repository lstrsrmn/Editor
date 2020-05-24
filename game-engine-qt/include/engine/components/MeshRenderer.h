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

//ENGINE_COMPONENT(MeshRenderer)
//CUSTOM_EDITOR(MeshRenderer) {
//    DISPLAY_EDITOR_VIEW(MeshRenderer) {
//        FileEventHandler* handler = new FileEventHandler(object->_material->filePath);
//        EditorFunctions::filePathInput(layout, "New Texture", handler);
//        UpdateEventHandler<Material*>* updateHandler = new UpdateEventHandler<Material*>(object->_material);
//        EditorFunctions::buttonInput(layout, "Update", updateHandler);
//      TODO: Need to make function below only get called after handler has received path.
//    }
//};
#endif //GAME_ENGINE_MESHRENDERER_H
