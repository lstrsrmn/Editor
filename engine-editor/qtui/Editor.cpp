#include "Editor.h"
#include "../build/ui_Editor.h"
#include <cstdio>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor){

    ui->setupUi(this);
    connect(ui->runStopButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(ui->ViewPort, SIGNAL(currentChanged(int)), this, SLOT(viewPortChanged(int)));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadScene()));
    //TODO: make scene display stuff and move around easily, then make loading models, then make game run scene, then make scenes savable
}

Editor::~Editor()
{
    delete ui;
}

void Editor::runButtonClicked() {
    _gameRunning = !_gameRunning;
//    ui->gameGLWidget->setEnabled(_gameRunning);
    if (_gameRunning) {
        ui->gameGLWidget->setEnabled(true);
        ui->runStopButton->setText("Stop");
        ui->ViewPort->setCurrentIndex(1);
    }
    else {
        ui->gameGLWidget->setEnabled(false);
        ui->runStopButton->setText("Run");
    }
}

void Editor::loadScene() {
    Scene* scene = SceneView::instance()->getCurrentScene();
    ui->hierarchyTree->clear();
    ui->hierarchyTree->setHeaderLabel(scene->getName());
    for (QString name : scene->getObjectNames()) {
        QTreeWidgetItem *node = new QTreeWidgetItem(ui->hierarchyTree->invisibleRootItem());
        node->setText(0, name);
    }
}

void Editor::viewPortChanged(int newViewPort) {
    ContextController::instance()->setCurrent(newViewPort);
    if (newViewPort == 0) {
        ui->gameGLWidget->setEnabled(false);
        ui->runStopButton->setText("Run");
    }
}
