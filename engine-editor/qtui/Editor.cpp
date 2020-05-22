#include "Editor.h"
#include "../build/ui_Editor.h"
#include <cstdio>
class myWidget: public QWidget {
signals:
    void sizeChange(const QSize &size) {emit size;};

    inline void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event);
        emit sizeChange(event->size());
    }
};

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor){

    ui->setupUi(this);
    connect(ui->runStopButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(ui->ViewPort, SIGNAL(currentChanged(int)), this, SLOT(viewPortChanged(int)));
    connect(ui->actionNew_Object, SIGNAL(triggered(bool)), this, SLOT(test(bool)));
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(loadScene()));
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
    GameObject* selectedObject = _treeObjectDir[selectedWidget];
    ui->inspectorObjects->setEnabled(true);



    for (int i = 0; i < ui->inspectorObjects->count() - 1; i++)
        ui->inspectorObjects->removeItem(1);
    for (Component* component: selectedObject->getComponents()) {
        QWidget* node = new QWidget();
        ui->inspectorObjects->addItem(node, component->componentName().c_str());
    }
    QWidget* transform = ui->inspectorObjects->widget(0);
//    transform = (myWidget*)transform;
    QScrollArea* frame = new QScrollArea(transform);
//    connect(transform, SIGNAL(sizeChange(const QSize)), frame, SLOT(resizeEvent(const QSize)));
    QVBoxLayout* layout = new QVBoxLayout;
    QTextBrowser* browser = new QTextBrowser();
    browser->setText("Current x, y, z positions");
    selectedObject->getTransform().setPos({1, 2, 3});
    QLCDNumber* xVal = new QLCDNumber();
    xVal->display(selectedObject->getTransform().getPos().x);
    QLCDNumber* yVal = new QLCDNumber();
    yVal->display(selectedObject->getTransform().getPos().y);
    QLCDNumber* zVal = new QLCDNumber();
    zVal->display(selectedObject->getTransform().getPos().z);
    layout->addWidget(browser);
    layout->addWidget(xVal);
    layout->addWidget(yVal);
    layout->addWidget(zVal);
    frame->setLayout(layout);
    frame->show();
}
