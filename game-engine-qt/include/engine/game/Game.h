#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H

#include <map>
#include <vector>
#include <string>
#include "Scene.h"
#include "../graphics/Display.h"
#include <QtOpenGL>

enum GameErrorCode {
    SUCCESS,
    ERROR_NO_SCENE
};
class Game {
public:
    static Game* instance();
    void makeDisplay(int, int, const std::string&);
    GameErrorCode run();
    void update();
    void addScene(Scene*);
    void setActive(unsigned int);
    Scene* activeScene();
    float getAR() const;
    void setAR(float);

    QOpenGLFunctions *getGlFunctions() const;

    void setGlFunctions(QOpenGLFunctions *glFunctions);

private:
    QOpenGLFunctions* _glFunctions;
    Game();
    Display* _display;
    static Game* _instance;
    std::map<unsigned int, Scene*> _scenes;
//    std::vector<Scene*> _scenes;
    unsigned int _activeScene;
};


#endif //GAME_ENGINE_GAME_H
