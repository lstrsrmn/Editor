#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

// includes all necicary packages
#include <QtOpenGL>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../editor/EditorView.h"
#include "../game/Scene.h"
//#include "../game/Game.h"

// defines camera class
class Camera {
   // befriends the editorview<Camera> class, so the editorView can access private functions and variables
    friend class EditorView<Camera>;
public:
    // defines constructor, const means pos cannot be changed by function
    Camera(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar, glm::vec3 = {0.3, 0.11, 0.11});
    
    // defines functions for getting the view projection matrix, const here means function wont affect class
    glm::mat4 getViewProjection() const;
    
    // function for moving the camera
    void moveBy(glm::vec3 movement);
    
    // returns right vector
    glm::vec3 getRight() const;

    // returns forward vector, first const means return object cannot be changed, second means function wont affect class
    const glm::vec3 &getForward() const;
    
    // makes the camera look at glm::vec3
    void lookAt(glm::vec3);

    // sets forward vector, const means input vector cannot be changed by function
    void setForward(const glm::vec3 &forward);
    
    // returns up vector,, first const means return object cannot be changed, second means function wont affect class
    const glm::vec3 &getUp() const;
    
    // sets up vector, const means object "up" cannot be changed by this function
    void setUp(const glm::vec3 &up);

    // sets camera clear colour
    void clear(float r, float g, float b, float a);

    // rotates the camera by x, y, z (radians)
    void rotateBy(float x, float y, float z);

    // moves camera to pos
    void moveTo(glm::vec3 pos);

    // returns camera position, first const means return object cannot be changed, second means function wont affect class
    const glm::vec3 &getPosition() const;
    
    // sets camera aspect ratio
    void setAR(float);

    // takes the camera object, and turns it into interpretable json code, saving the state of the camera object
    void serializeToJSON(nlohmann::json&);

    // turns a save of the camera into a camera object, static because its more efficient and means no default constructor needed
    static Camera* deserializeFromJSON(nlohmann::json&);
    
    // defines public variables
    glm::vec3 ambient, position;
    Scene* _scene;

private:
    // defines private variables
    float _fov, _zNear, _zFar;
    glm::mat4 _perspective;
    glm::vec3 _forward, _up;
};

CUSTOM_EDITOR(Camera) {
    DISPLAY_EDITOR_VIEW(Camera) {
        // sets position variables (x, y, z) to be editable from the editor
        EditorFunctions::label(layout, "Position");
        EditorFunctions::floatInput(layout, "x: ", object->position.x);
        EditorFunctions::floatInput(layout, "y: ", object->position.y);
        EditorFunctions::floatInput(layout, "z: ", object->position.z);

        EditorFunctions::label(layout, "Ambient");
        EditorFunctions::floatInput(layout, "r: ", object->ambient.r);
        EditorFunctions::floatInput(layout, "g: ", object->ambient.g);
        EditorFunctions::floatInput(layout, "b: ", object->ambient.b);
    }
};

#endif //GAME_ENGINE_CAMERA_H
