//#include "include/graphics/Display.h"
//#include "include/graphics/Shader.h"
//#include "include/graphics/Mesh.h"
//#include "include/graphics/Texture.h"
//#include "include/game/Transform.h"
//#include "include/graphics/Camera.h"
//#include "include/graphics/ModelImporter.h"
//#include "include/components/MeshRenderer.h"
//#include "include/game/GameObject.h"
//#include "include/game/Scene.h"
//#include "include/game/Game.h"
//
//int main() {
//    Display display(640, 400, "title");
//
//    Game* game = Game::instance();
//
//    Shader shader("/home/lstrsrmn/CLionProjects/game-engine-qt/res/basicShader");
//    Texture sTexture("/home/lstrsrmn/CLionProjects/game-engine-qt/res/bricks.jpg");
//    Texture mTexture("/home/lstrsrmn/CLionProjects/game-engine-qt/res/monkeyDiffuse.jpg");
//
//    Material sMaterial(&shader, &sTexture);
//    Material mMaterial(&shader, &mTexture);
//
//    Camera camera(glm::vec3(0,0,-5), 70.0f, display.getAR(), 0.01f, 1000.0f);
//    Transform transform;
//    Transform transform2;
//    float counter = 0.0f;
//
////    Vertex vertices[] = {
////            Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
////            Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
////            Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
////    };
////
////    unsigned int indices[] = {0, 1, 2};
////
////    Mesh mesh(vertices, sizeof(vertices) / sizeof(Vertex), indices, sizeof(indices) / sizeof(indices[0]));
//
//    ModelMeshData sphere = loadModel("/home/lstrsrmn/CLionProjects/game-engine-qt/res/models/default/Sphere.fbx");
//    ModelMeshData monkey = loadModel("/home/lstrsrmn/CLionProjects/game-engine-qt/res/models/default/Monkey.fbx");
//
//    MeshRenderer mRenderer(&mMaterial, monkey);
//    MeshRenderer sRenderer(&sMaterial, sphere);
//
//    DirectionalLight light(glm::vec3(0, 0, 1), glm::vec3(1, 1, 1));
//
//    Scene scene(&camera, light);
//
//    GameObject* sObj = scene.createGameObject();
//    GameObject* mObj = scene.createGameObject();
//
//    mObj->addComponent(&mRenderer);
//    sObj->addComponent(&sRenderer);
//    game->addScene(&scene);
//    game->setActive(0);
//
//
//    while (!display.closed()) {
//        display.clear(0.0f, 0.15f, 0.3f, 1.0f);
//
//        float sinCounter = sinf(counter);
//        float cosCounter = cosf(counter);
////
////        transform2.getPos().z = sinCounter;
////
////        transform.getRot().x = 3.1415 / 2;
////        transform.getRot().z = 3.1415;
//////        transform.getRot().y = counter;
////        shader.bind();
////        texture.bind(0);
////        shader.update(transform, camera);
////        sphere.meshes[0]->draw();
////
////
//        counter += 0.5f;
//        game->update();
//
//        camera.moveBy(glm::vec3(0, 0, -0.01));
//
//        display.update();
//    }
//
//    return 0;
//}
