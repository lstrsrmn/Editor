#ifndef GAME_ENGINE_SCENE_H
#define GAME_ENGINE_SCENE_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "../core/Utils.h"
#include "Game.h"
#include "SceneView.h"

class Camera;
class DirectionalLight;
class GameObject;
class Renderer;
class SceneManager;
class ModelMeshData;
struct ModelMeshTree;
class Material;

class Scene {
public:
    Scene(Camera*, DirectionalLight*);

    void update();
    
    // draws to the camera stored locally
    void draw();

    // draws to the camera passed in
    void draw(Camera *);

    GameObject *createGameObject();

    GameObject *createGameObjectsFromMeshData(ModelMeshData*, Material*);

    void addRenderer(Renderer *);

    unsigned int getId() const;

    void setAR(float);

    const QString &getName() const;

    void setName(const QString &name);

    std::vector<GameObject *> getObjects();

    void deleteObject(GameObject*);

    void deleteRenderer(Renderer*);

    void serializeToJSON();

    static Scene* deserializeFromJSON(const std::string&);

    std::filesystem::path _fileLocation;

    Camera *getCamera() const;

    DirectionalLight* getDirectionalLight() const;

    void updateMaterials();

private:
    GameObject* getObjectByID(unsigned int);
    unsigned int currentObjectID = 0;
    GameObject* createGameObjectFromTree(GameObject*, ModelMeshTree*, Material*);
    QString _name;
    unsigned int _id;
    DirectionalLight *_directionalLight;
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
