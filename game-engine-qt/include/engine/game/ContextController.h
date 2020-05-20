//
// Created by lstrsrmn on 19/05/2020.
//

#ifndef ENGINE_EDITOR_CONTEXTCONTROLLER_H
#define ENGINE_EDITOR_CONTEXTCONTROLLER_H

#include "Game.h"
#include "SceneView.h"

class ContextController {
public:
    static ContextController* instance();
    void setSceneGLFunctions(QOpenGLFunctions*);
    void setGameGLFunctions(QOpenGLFunctions*);
    void setCurrent(int current);
    QOpenGLFunctions* getCurrentContext();

private:
    ContextController();
    static ContextController* _instance;
    QOpenGLFunctions* _GLFunctions[2];
    int _current = 0;
};


#endif //ENGINE_EDITOR_CONTEXTCONTROLLER_H
