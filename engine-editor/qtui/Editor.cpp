#include "Editor.h"
#include "../build/ui_Editor.h"

Editor::Editor(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Editor) {

    ui->setupUi(this);
    ui->hierarchyTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->runStopButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(ui->ViewPort, SIGNAL(currentChanged(int)), this, SLOT(viewPortChanged(int)));
//    connect(ui->actionNew_Object, SIGNAL(triggered(bool)), this, SLOT(loadObject(bool)));
    connect(ui->hierarchyTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)), this,
            SLOT(objectSelected(QTreeWidgetItem * , int)));
    connect(ui->projectTree, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this,
            SLOT(updateOpenFolder(QTreeWidgetItem * , int)));
    connect(ui->folderContents, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(loadTableItem(QTableWidgetItem*)));
    connect(ui->hierarchyTree, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(hierarchyMenu(const QPoint&)));
    //TODO: make scene display stuff and move around easily, then make loading models, then make game run scene, then make scenes savable
    updateProject();

}

Editor::~Editor() {
    delete ui;
}

void Editor::runButtonClicked() {
    _gameRunning = !_gameRunning;
//    ui->gameGLWidget->setEnabled(_gameRunning);
    if (_gameRunning) {
        ui->gameGLWidget->setEnabled(true);
        ui->runStopButton->setText("Stop");
        ui->ViewPort->setCurrentIndex(1);
    } else {
        ui->gameGLWidget->setEnabled(false);
        ui->runStopButton->setText("Run");
    }
}

void Editor::loadScene() {
    Scene *scene = SceneView::instance()->getCurrentScene();
    ui->hierarchyTree->clear();
    _treeObjectDir.clear();
    ui->hierarchyTree->setHeaderLabel(scene->getName());
    for (GameObject *object : scene->getObjects()) {
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

void Editor::loadObject(bool) {
    QString filePath = QFileDialog::getOpenFileName(this, "Open model", QApplication::applicationDirPath());
    ModelMeshData input = loadModel(filePath.toStdString());
    loadObject(filePath.toStdString());
}

void Editor::loadObject(const std::string& filePath) {
    const std::filesystem::path path = filePath;
    std::string fileName = removeExtention(path.filename().string());
    Scene *scene = SceneView::instance()->getCurrentScene();
    ModelMeshData input = loadModel(filePath);

    Texture *texture = Texture::createTexture("res/textures/defaultDiffuse.jpg");
    Shader *shader = new Shader("basicShader");
    Material *material = new Material(shader, texture);

    MeshRenderer *newRenderer = new MeshRenderer(material, input);
    GameObject *newObj = scene->createGameObject();
    newObj->setName(fileName.c_str());
    newObj->addComponent(newRenderer);
    loadScene();
    ui->sceneGLWidget->update();
    newObj->getTransform().pos = {0, 0, 0};
}
void Editor::objectSelected(QTreeWidgetItem *selectedWidget, int column) {
    _selectedObject = _treeObjectDir[selectedWidget];
    ui->inspectorObjects->setEnabled(true);


    for (int i = 0; i < ui->inspectorObjects->count() - 1; i++)
        ui->inspectorObjects->removeItem(1);
    for (Component *component: _selectedObject->getComponents()) {
        QWidget *node = new QWidget();
        ui->inspectorObjects->addItem(node, component->componentName().c_str());
    }
    QWidget *transform = ui->inspectorObjects->widget(0);
    QFrame *tFrame = new QFrame(transform);
    QFormLayout *tLayout = new QFormLayout;
    EditorView<Transform>::displayEditorView(&_selectedObject->getTransform(), tLayout);
    tFrame->setLayout(tLayout);
    tFrame->show();

//    QWidget* meshRenderer = ui->inspectorObjects->widget(1);
//    QFrame* mFrame = new QFrame(meshRenderer);
//    QFormLayout* mLayout = new QFormLayout;
//    EditorView<MeshRenderer>::displayEditorView((MeshRenderer*)_selectedObject->getComponents().front(), mLayout);
//    mFrame->setLayout(mLayout);
//    mFrame->show();

}

void Editor::updateProject() {
    QTreeWidget *projectTree = ui->projectTree;
    QTreeWidgetItem *root = projectTree->invisibleRootItem();
    root->setText(0, projectDir.c_str());
    recurseProjectTree(projectDir, root);
}

void Editor::recurseProjectTree(const std::string &filePath, QTreeWidgetItem *parent) {
    for (const auto &entry : std::filesystem::directory_iterator(filePath)) {
        if (entry.is_directory()) {
            QTreeWidgetItem *item = new QTreeWidgetItem(parent);
            item->setText(0, entry.path().filename().c_str());
            recurseProjectTree(entry.path(), item);
        }
    }
}

void Editor::updateOpenFolder(QTreeWidgetItem *item, int) {
    folderPath = item->text(0).toStdString();
    QTreeWidgetItem *parent = item->parent();
    while (parent != nullptr) {
        folderPath.insert(0, parent->text(0).toStdString() + "/");
        parent = parent->parent();
    }
    folderPath.insert(0, projectDir + "/");

    ui->folderContents->clear();
    ui->folderContents->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->folderContents->setRowCount(0);
    ui->folderContents->setColumnCount(0);
    ui->folderContents->setColumnCount(ui->folderContents->width() / 100);
    for (int i = 0; i < ui->folderContents->columnCount(); i++)
        ui->folderContents->setColumnWidth(i, 100);
    unsigned int counter = 0;
    int columnCount = ui->folderContents->columnCount();
    for (const auto &entry : std::filesystem::directory_iterator(folderPath)) {
        if (!entry.is_directory()) {
            if (counter >= ui->folderContents->rowCount() * columnCount) {
                ui->folderContents->setRowCount(ui->folderContents->rowCount() + 1);
            }
            QTableWidgetItem *tableItem = new QTableWidgetItem(entry.path().filename().c_str());
            tableItem->setTextAlignment(Qt::AlignCenter);
            ui->folderContents->setItem(counter / columnCount,
                                        counter % columnCount,
                                        tableItem);
            counter++;
        }
    }
}

void Editor::loadTableItem(QTableWidgetItem* item) {
    std::string filePath = folderPath + "/" + item->text().toStdString();
    const std::filesystem::path path = filePath;
    const std::string ext = path.extension().string();
    if (ext == ".mat") {
        std::cout << "material" << std::endl;
    }
    else if (ext == ".jpg" || ext == ".png") {
        std::cout << "texture" << std::endl;
    }
    else if (ext == ".fbx") {
        loadObject(filePath);
    }
    else if (ext == ".vs") {
        std::cout << "vertex shader" << std::endl;
    }
    else if (ext == ".fs") {
        std::cout << "fragment shader" << std::endl;
    }
    else {
        QMessageBox::warning(this, tr("Wrong file format"), tr("An unloadable file has been selected, please select another."));
    }
}

void Editor::hierarchyMenu(const QPoint& point) {
    QTreeWidgetItem* clicked = ui->hierarchyTree->itemAt(point);
    if (clicked != nullptr) {
        ui->hierarchyTree->clearSelection();
        clicked->setSelected(true);
        objectSelected(clicked, 0);
        QMenu* menu = new QMenu("menu");

        // Rename
        QAction* renamed = new QAction();
        renamed->setText("Rename");
        menu->addAction(renamed);
        connect(renamed, SIGNAL(triggered(bool)), this, SLOT(renameObject(bool)));
        menu->popup(QCursor::pos());

        // Delete
        QAction* deleteObject = new QAction();
        deleteObject->setText("Delete");
        menu->addAction(deleteObject);
        connect(deleteObject, SIGNAL(triggered(bool)), this, SLOT(deleteObject(bool)));

        // Set Focus
        QAction* setFocus = new QAction();
        setFocus->setText("Set Focus");
        menu->addAction(setFocus);
        connect(setFocus, SIGNAL(triggered(bool)), this, SLOT(setSceneViewFocus(bool)));
    }
}

void Editor::renameObject(bool) {
    QString input = QInputDialog::getText(this, "Rename", "Input new name of " + _selectedObject->getName());
    _selectedObject->setName(input);
    ui->hierarchyTree->selectedItems()[0]->setText(0, input);
}

void Editor::deleteObject(bool) {
    delete _selectedObject;
    loadScene();
    ui->inspectorObjects->setEnabled(false);
}

void Editor::setSceneViewFocus(bool) {
    ui->sceneGLWidget->setFocus(_selectedObject->getTransform().pos);
}






std::string removeExtention(const std::string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}

