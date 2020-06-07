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
    void setSceneGL(QOpenGLFunctions*, QOpenGLWidget*);
//    void setSceneGLCallbacks(std::function<void()>, std::function<void()>);
    void setGameGL(QOpenGLFunctions*, QOpenGLWidget*);
//    void setGameGLCallbacks(std::function<void()>, std::function<void()>);
    void setCurrent(int current);
    int getCurrent() const;
    QOpenGLFunctions* getCurrentFunctions();
    QOpenGLContext* getSceneContext();

private:
    ContextController();
    static ContextController* _instance;
    QOpenGLFunctions* _GLFunctions[2] = {nullptr, nullptr};
    QOpenGLWidget* _GLWidgets[2] = {nullptr, nullptr};
//    std::function<void()> sMakeCurrent, sCreateContextFunctions, gMakeCurrent, gCreateContextFunctions;
    int _current = 0;
};


#endif //ENGINE_EDITOR_CONTEXTCONTROLLER_H
