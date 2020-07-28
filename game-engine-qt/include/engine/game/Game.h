#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H

#include <map>
#include <vector>
#include <string>
#include <QtOpenGL>

class Scene;

enum GameErrorCode {
    SUCCESS,
    ERROR_NO_SCENE
};
class Game {
public:
    static Game* instance();
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
    static Game* _instance;
    std::map<unsigned int, Scene*> _scenes;
    unsigned int _activeScene;
    float _AR;
};


#endif //GAME_ENGINE_GAME_H
