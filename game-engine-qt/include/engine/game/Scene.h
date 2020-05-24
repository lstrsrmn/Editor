#ifndef GAME_ENGINE_SCENE_H
#define GAME_ENGINE_SCENE_H

#include <vector>
#include <string>
#include "../components/Renderer.h"
#include "GameObject.h"
#include "../graphics/lighting/DirectionalLight.h"

class SceneManager;

class Scene {
public:
    Scene(Camera *camera, DirectionalLight);

    void update();

    void draw();

    void draw(Camera *);

    GameObject *createGameObject();

    void addRenderer(Renderer *);

    unsigned int getId() const;

    void setAR(float);

    const QString &getName() const;

    void setName(const QString &name);

    std::vector<GameObject *> getObjects();

    void deleteObject(GameObject*);

    void deleteRenderer(Renderer*);

private:
    QString _name;
    unsigned int _id;
    DirectionalLight _directionalLight;
    Camera *_camera;
    std::vector<GameObject *> _gameObjects;
    std::vector<Renderer *> _renderers;
};

class SceneManager {
public:
    static SceneManager *instance();

    unsigned int addScene(Scene *);

private:
    unsigned int _numScenes = 0;
    static SceneManager *_instance;
    std::vector<Scene *> _scenes;
};

#endif //GAME_ENGINE_SCENE_H
