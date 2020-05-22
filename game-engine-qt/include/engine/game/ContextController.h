//
// Created by lstrsrmn on 19/05/2020.
//

#ifndef ENGINE_EDITOR_CONTEXTCONTROLLER_H
#define ENGINE_EDITOR_CONTEXTCONTROLLER_H

#include "Game.h"
#include "SceneView.h"

class SceneGLView;
class GameGLView;

class ContextController {
public:
    static ContextController* instance();
    void setSceneGLFunctions(QOpenGLFunctions*, SceneGLView*);
    void setGameGLFunctions(QOpenGLFunctions*, GameGLView*);
    void setCurrent(int current);
    QOpenGLFunctions* getCurrentContext();

private:
    ContextController();
    static ContextController* _instance;
    QOpenGLFunctions* _GLFunctions[2];
    QOpenGLWidget* _GLWidgets[2];
    int _current = 0;
};


#endif //ENGINE_EDITOR_CONTEXTCONTROLLER_H
