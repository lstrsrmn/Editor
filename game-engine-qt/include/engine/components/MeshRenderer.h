#ifndef GAME_ENGINE_MESHRENDERER_H
#define GAME_ENGINE_MESHRENDERER_H

#include "Renderer.h"
#include "../editor/EditorView.h"

#include "../graphics/ModelImporter.h"

class MeshRenderer;
class Material;

CUSTOM_EDITOR(MeshRenderer) {
    static void displayEditorView(MeshRenderer *object, QFormLayout *layout);
    static std::map<std::string, Material*> materialChoice;
};

class MeshRenderer : public Renderer {
    SUBSCRIBE_COMPONENT(MeshRenderer)
public:
    MeshRenderer(Material*, Mesh*);
    void render(const Camera&, DirectionalLight*) override;
    Material* _material;
    void updateMaterial(const QString&);
    void serializeToJSON(nlohmann::json&) override;
    static MeshRenderer* deserializeFromJSON(nlohmann::json&);
private:
    Mesh* _mesh;

    // TODO: vector of materials instead of 1
};



#endif //GAME_ENGINE_MESHRENDERER_H
