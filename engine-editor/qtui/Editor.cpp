#include "Editor.h"
#include "../build/ui_Editor.h"
#include <cstdio>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor){

    ui->setupUi(this);
    connect(ui->runStopButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(ui->ViewPort, SIGNAL(currentChanged(int)), this, SLOT(viewPortChanged(int)));
    connect(ui->actionNew_Object, SIGNAL(triggered(bool)), this, SLOT(test(bool)));
    connect(ui->hierarchyTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(objectSelected(QTreeWidgetItem*, int)));
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
    _treeObjectDir.clear();
    ui->hierarchyTree->setHeaderLabel(scene->getName());
    for (GameObject* object : scene->getObjects()) {
        QTreeWidgetItem *node = new QTreeWidgetItem(ui->hierarchyTree->invisibleRootItem());
        node->setText(0, object->getName());
        _treeObjectDir[node] = object;
    }
}

void Editor::viewPortChanged(int newViewPort) {
    ContextController::instance()->setCurrent(newViewPort);
    if (newViewPort == 0) {
        ui->gameGLWidget->setEnabled(false);
        ui->runStopButton->setText("Run");
    }
}

void Editor::test(bool t) {
    QString filePath = QFileDialog::getOpenFileName(this, "Open model", QApplication::applicationDirPath());
    Scene* scene = SceneView::instance()->getCurrentScene();
    ModelMeshData input = loadModel(filePath.toStdString());

    Texture *texture = new Texture("monkeyDiffuse2.jpg");
    Shader *shader = new Shader("basicShader");
    Material *material = new Material(shader, texture);

    MeshRenderer* newRenderer = new MeshRenderer(material, input);
    GameObject* newObj = scene->createGameObject();
    newObj->setName("New Object");
    newObj->addComponent(newRenderer);
    loadScene();
    ui->sceneGLWidget->update();
    newObj->getTransform().setPos({0, 0, 0});
}

void Editor::objectSelected(QTreeWidgetItem *selectedWidget, int column) {
    _selectedObject = _treeObjectDir[selectedWidget];
    ui->inspectorObjects->setEnabled(true);



    for (int i = 0; i < ui->inspectorObjects->count() - 1; i++)
        ui->inspectorObjects->removeItem(1);
    for (Component* component: _selectedObject->getComponents()) {
        QWidget* node = new QWidget();
        ui->inspectorObjects->addItem(node, component->componentName().c_str());
    }
    transform = ui->inspectorObjects->widget(0);
    QFrame* frame = new QFrame(transform);
    QFormLayout* layout = new QFormLayout;
    QLabel* label = new QLabel;
    QValidator *v = new QDoubleValidator(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), 4);
    for (int i = 0; i < 3; i++) {
        _textEdits[i] = new QLineEdit();
        _textEdits[i]->setValidator(v);
    }
    QPushButton* inputButton = new QPushButton();
    label->setText("Update x, y and z coords between -999 and 999: ");
    inputButton->setText("Update");
    layout->addRow(label);
    layout->addRow(tr("x"), _textEdits[0]);
    layout->addRow(tr("y"), _textEdits[1]);
    layout->addRow(tr("z"), _textEdits[2]);
    layout->addRow(inputButton);
    frame->setLayout(layout);
    frame->show();
    connect(inputButton, SIGNAL(clicked()), this, SLOT(updateTransform()));
}

void Editor::updateTransform() {
    _selectedObject->getTransform().setPos({_textEdits[0]->text().toFloat(), _textEdits[1]->text().toFloat(), _textEdits[2]->text().toFloat()});
}
