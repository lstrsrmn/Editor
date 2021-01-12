#ifndef GAME_ENGINE_GAME_H
#define GAME_ENGINE_GAME_H

#include <map>
#include <vector>
#include <string>
#include <QtOpenGL>

// forward delcares scene
class Scene;

enum GameErrorCode {
    SUCCESS,
    ERROR_NO_SCENE
};
// singleton class
class Game {
public:
    static Game* instance();
    // renders all objects
    GameErrorCode run();
    // updates game
    void update();
    void addScene(Scene*);
    // sets the active scene
    void setActive(unsigned int);
    Scene* activeScene();
    // gets and sets aspect ratio
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
