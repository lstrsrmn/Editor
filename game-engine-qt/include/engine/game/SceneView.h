//
// Created by lstrsrmn on 19/05/2020.
//

#ifndef ENGINE_EDITOR_SCENEVIEW_H
#define ENGINE_EDITOR_SCENEVIEW_H

#include <vector>
#include <map>
#include "Scene.h"
#include "../core/Utils.h"

class SceneView {
public:
    static SceneView* instance();
    void addScene(Scene* scene);
    Scene* getCurrentScene();
    void setActive(unsigned int);
    void makeCamera();
    Camera* getCamera();
    float getAR() const;
    void update();
    void setAR(float ar);
    void pan(glm::vec2);
    void orbit(glm::vec2);
    void zoom(float);
    QOpenGLFunctions *getGlFunctions() const;

    void setGlFunctions(QOpenGLFunctions *glFunctions);

private:
    glm::vec3 _focus{0, 0, 0};
    SceneView();
    unsigned int _activeScene;
    static SceneView* _instance;
    std::map<unsigned int, Scene*> _scenes;
    Camera* _sceneCamera = nullptr;
    float _AR = 0;
    QOpenGLFunctions* _glFunctions;
};


#endif //ENGINE_EDITOR_SCENEVIEW_H
