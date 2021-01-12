#ifndef ENGINE_EDITOR_CONTEXTCONTROLLER_H
#define ENGINE_EDITOR_CONTEXTCONTROLLER_H

#include "Game.h"
#include "SceneView.h"

// previously used, not anymore

class SceneGLView;
class GameGLView;

class ContextController {
public:
    static void setGL(QOpenGLFunctions*, QOpenGLWidget*);
    static QOpenGLFunctions* getFunctions();
    static QOpenGLContext* getContext();

private:
    static ContextController* instance();
    ContextController();
    static ContextController* _instance;
    QOpenGLFunctions* _GLFunctions = nullptr;
    QOpenGLWidget* _GLWidget = nullptr;
};


#endif //ENGINE_EDITOR_CONTEXTCONTROLLER_H
