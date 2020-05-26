#include <iostream>
//#include <engine/Core.h>
//#include <engine/Objects.h>
#include <QApplication>
#include <QtGui/QSurfaceFormat>
#include "qtui/Editor.h"
//#include "qtui/test.h"
//#include "widgets/GameGLView.h"

//int run_game() {
//    Game* game = Game::instance();
//
//    game->makeDisplay(1920, 1080, "Editor");
//
//    Texture texture("monkeyDiffuse.jpg");
//    Shader shader("basicShader");
//    ModelMeshData monkeyModel = loadModel("Monkey.fbx");
//
//    Material material(&shader, &texture);
//
//    MeshRenderer meshRenderer(&material, monkeyModel);
//
//    Camera camera(glm::vec3(0, 0, -3), 70, game->getAR(), 0.01, 1000);
//
//    DirectionalLight directionalLight;
//
//    Scene scene = Scene(&camera, directionalLight);
//
//    GameObject* monkey = scene.createGameObject();
//
//    monkey->addComponent(&meshRenderer);
//
//    game->addScene(&scene);
//    game->setActive(0);
//
//    switch(game->run()) {
//        case SUCCESS:
//            break;
//        case ERROR_NO_SCENE:
//            printf("Error: No scene found\n");
//            return -1;
//    }
//
//    return 0;
//}

int main(int argc, char* argv[]) {
//    return run_game();
    QApplication app(argc, argv);


//    QSurfaceFormat fmt;
//    fmt.setDepthBufferSize(24);
//    fmt.setVersion(4, 6);
//    fmt.setProfile(QSurfaceFormat::CoreProfile);
//    QSurfaceFormat::setDefaultFormat(fmt);

    Editor* editor = new Editor();
    editor->setMinimumSize(QSize(800, 600));
    editor->setWindowTitle("Engine Editor");
    editor->showMaximized();
    return QApplication::exec();
}