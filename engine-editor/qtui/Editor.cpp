#include "Editor.h"
#include "../build/ui_Editor.h"

Editor::Editor(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Editor) {

    ui->setupUi(this);
    ui->hierarchyTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->runStopButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(ui->ViewPort, SIGNAL(currentChanged(int)), this, SLOT(viewPortChanged(int)));
    connect(ui->actionNew_Object, SIGNAL(triggered(bool)), this, SLOT(loadObject(bool)));
    connect(ui->hierarchyTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem * , int)), this,
            SLOT(objectSelected(QTreeWidgetItem * , int)));
    connect(ui->projectTree, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this,
            SLOT(updateOpenFolder(QTreeWidgetItem * , int)));
    connect(ui->folderContents, SIGNAL(itemDoubleClicked(QTableWidgetItem * )), this,
            SLOT(loadTableItem(QTableWidgetItem * )));
    connect(ui->hierarchyTree, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(hierarchyMenu(const QPoint&)));
    connect(ui->actionNew_Project, SIGNAL(triggered(bool)), this, SLOT(newProject(bool)));
    connect(ui->actionOpen_Project, SIGNAL(triggered(bool)), this, SLOT(loadProject(bool)));
    connect(ui->actionTextures, SIGNAL(triggered(bool)), this, SLOT(textureManager(bool)));
    connect(ui->actionMaterials, SIGNAL(triggered(bool)), this, SLOT(materialManager(bool)));
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

void Editor::loadObject(const std::string &filePath) {
    const std::filesystem::path path = filePath;
    std::string fileName = removeExtension(path.filename().string());
    Scene *scene = SceneView::instance()->getCurrentScene();
    ModelMeshData input = loadModel(filePath);

    Texture *texture = Texture::createTexture("DefaultDiffuse", "res/textures/defaultDiffuse.jpg");
    Shader *shader = Shader::createShader("BasicShader", "basicShader");
    Material *material = Material::createMaterial("DefaultMaterial", projectDir + "/Assets/Materials", shader, texture);

    MeshRenderer *newRenderer = new MeshRenderer(material, input);
    GameObject *newObj = scene->createGameObject();
    newObj->setName(fileName.c_str());
    newObj->addComponent(newRenderer);
    loadScene();
    ui->sceneGLWidget->update();
    newObj->getTransform().pos = {0, 0, 0};

    saveProjectMeta();
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
        if (entry.is_directory() && entry.path().filename().string() != "meta") {
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

void Editor::loadTableItem(QTableWidgetItem *item) {
    std::string filePath = folderPath + "/" + item->text().toStdString();
    const std::filesystem::path path = filePath;
    const std::string ext = path.extension().string();
    if (ext == ".mat") {
        std::cout << "material" << std::endl;
    } else if (ext == ".jpg" || ext == ".png") {
        QString name = QInputDialog::getText(this, "New Texture", "Please name your new Texture.");
        if (!name.isEmpty())
            createTexture(name.toStdString(), filePath);
    } else if (ext == ".fbx") {
        loadObject(filePath);
    } else if (ext == ".vs") {
        std::cout << "vertex shader" << std::endl;
    } else if (ext == ".fs") {
        std::cout << "fragment shader" << std::endl;
    } else {
        QMessageBox::warning(this, tr("File Format"),
                             tr("This is not a recognised file format."));
    }
}

void Editor::hierarchyMenu(const QPoint &point) {
    QTreeWidgetItem *clicked = ui->hierarchyTree->itemAt(point);
    if (clicked != nullptr) {
        ui->hierarchyTree->clearSelection();
        clicked->setSelected(true);
        objectSelected(clicked, 0);
        QMenu *menu = new QMenu("menu");

        // Rename
        QAction *renamed = new QAction();
        renamed->setText("Rename");
        menu->addAction(renamed);
        connect(renamed, SIGNAL(triggered(bool)), this, SLOT(renameObject(bool)));
        menu->popup(QCursor::pos());

        // Delete
        QAction *deleteObject = new QAction();
        deleteObject->setText("Delete");
        menu->addAction(deleteObject);
        connect(deleteObject, SIGNAL(triggered(bool)), this, SLOT(deleteObject(bool)));

        // Set Focus
        QAction *setFocus = new QAction();
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

void Editor::newProject(bool) {
    saveProjectMeta();
}

void Editor::saveProjectMeta() {
    mkdir((projectDir + "/meta").c_str(), 0777);
    std::string projectMetaDir = projectDir + "/meta/";
    std::ofstream projectMeta(projectMetaDir + "project.meta");
    nlohmann::json project;
    project["name"] = "Test Project";
    projectMeta << project.dump(4) << std::endl;
    projectMeta.close();
    AssetManager<Texture>::writeAssetMeta(projectMetaDir + "textures.meta");
    AssetManager<Shader>::writeAssetMeta(projectMetaDir + "shaders.meta");
    AssetManager<Material>::writeAssetMeta(projectMetaDir + "materials.meta");
}

void Editor::loadProject(bool) {
    const std::string projectMetaDir = projectDir + "/meta/";
    std::ifstream projectMeta(projectMetaDir + "project.meta");
    nlohmann::json project;
    projectMeta >> project;
    projectMeta.close();
    AssetManager<Texture>::readAssetMeta(projectMetaDir + "textures.meta");
    AssetManager<Shader>::readAssetMeta(projectMetaDir + "shaders.meta");
    AssetManager<Material>::readAssetMeta(projectMetaDir + "materials.meta");
}

void Editor::textureManager(bool) {
    QWidget* manager = new QWidget();
    manager->setAttribute(Qt::WA_DeleteOnClose, true);
    QHBoxLayout* managerLayout = new QHBoxLayout();
    manager->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, manager->size(), QGuiApplication::screens()[0]->geometry()));
    manager->setWindowTitle("Texture Manager");
    texturesList = new QListWidget;
    texturesList->setAttribute(Qt::WA_DeleteOnClose, false);
//    texturesList->setSelectionBehavior( QAbstractItemView::SelectItems );
//    texturesList->setSelectionMode( QAbstractItemView::SingleSelection );
    connect(texturesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(textureSelected(QListWidgetItem*)));
    updateTextureManager();
    managerLayout->addWidget(texturesList);
    texturesList->setParent(manager);

    QFrame* newTextures = new QFrame();
    QFormLayout* newTexturesLayout = new QFormLayout();
    QPushButton* loadProject = new QPushButton("Load Project Textures");
    QPushButton* newTexture = new QPushButton("Create new Texture");
    connect(loadProject, SIGNAL(clicked(bool)), this, SLOT(loadProject(bool)));
    connect(loadProject, SIGNAL(clicked()), this, SLOT(updateTextureManager()));
    connect(newTexture, SIGNAL(clicked()), this, SLOT(createTextureFromFile()));
    newTexturesLayout->addRow(loadProject);
    newTexturesLayout->addRow(newTexture);


    newTextures->setLayout(newTexturesLayout);
    managerLayout->addWidget(newTextures);
    manager->setLayout(managerLayout);
    manager->show();
}

void Editor::updateTextureManager() {
    texturesList->clear();
    std::map<unsigned int, Texture *> loadedTextures = AssetManager<Texture>::getLoadedAssets();
    for (std::pair<unsigned int, Texture*> texturePair: loadedTextures) {
        QListWidgetItem* item = new QListWidgetItem(texturePair.second->name.c_str());
        _listTextureDir[item] = texturePair.second;
        texturesList->addItem(item);
    }
}

void Editor::createTextureFromFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Texture", QString(projectDir.c_str()));
    QString name = QInputDialog::getText(this, "New Texture", "Please name your new Texture.");
    if (!filePath.isEmpty() && !name.isEmpty())
        createTexture(name.toStdString(), filePath.toStdString());
}

void Editor::createTexture(const std::string &name, const std::string &filePath) {
    AssetManager<Texture>::createAsset(name, filePath);
    updateTextureManager();
    saveProjectMeta();
}

void Editor::deleteTexture() {
    //TODO: impliment deleting
}

void Editor::textureSelected(QListWidgetItem* item) {
    _selectedTexture = _listTextureDir[item];
    QString filePath(_selectedTexture->getFilePath().c_str());
    QWidget* imageWindow = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    QLabel* imageLabel = new QLabel(imageWindow);
    QImageReader reader(filePath);
    reader.setAutoTransform(true);
    const QImage image = reader.read();
    imageLabel->setPixmap(QPixmap::fromImage(image.scaled(512, 512)));
    layout->addWidget(imageLabel);

    QPushButton* deleteButton = new QPushButton("Delete");
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteTexture()));
    layout->addWidget(deleteButton);

    imageWindow->setLayout(layout);
    imageWindow->show();
}

void Editor::materialManager(bool) {
    QWidget* window = new QWidget();

    window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window->size(), QGuiApplication::screens()[0]->geometry()));
    window->setWindowTitle("Material Manager");

    QHBoxLayout* layout = new QHBoxLayout();

    materialsList = new QListWidget();
    updateMaterialManager();
    connect(materialsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(materialSelected(QListWidgetItem*)));
    layout->addWidget(materialsList);

    QFrame* frame = new QFrame();
    QFormLayout* frameLayout = new QFormLayout();
    QPushButton* loadMaterial = new QPushButton("Load Project Materials");
    connect(loadMaterial, SIGNAL(clicked(bool)), this, SLOT(loadProject(bool)));
    connect(loadMaterial, SIGNAL(clicked()), this, SLOT(updateMaterialManager()));
    QPushButton* newMaterial = new QPushButton("Create new Material");
    connect(newMaterial, SIGNAL(clicked()), this, SLOT(createMaterial()));
    frameLayout->addRow(loadMaterial);
    frameLayout->addRow(newMaterial);
    frame->setLayout(frameLayout);
    layout->addWidget(frame);
    window->setLayout(layout);
    window->show();
}

void Editor::createMaterial() {
    QWidget* widget = new QWidget();
    widget->setWindowTitle("Choose Texture");
    QVBoxLayout* layout = new QVBoxLayout();

    newMaterialList = new QListWidget();
    newMaterialList->clear();
    std::map<unsigned int, Texture *> loadedTextures = AssetManager<Texture>::getLoadedAssets();
    for (std::pair<unsigned int, Texture*> texturePair: loadedTextures) {
        QListWidgetItem* item = new QListWidgetItem(texturePair.second->name.c_str());
        _listForNewMaterialDir[item] = texturePair.second;
        newMaterialList->addItem(item);
    }
    layout->addWidget(newMaterialList);

    QFrame* frame = new QFrame();
    QHBoxLayout* frameLayout = new QHBoxLayout();
    QPushButton* selectButton = new QPushButton("Select");
    connect(selectButton, SIGNAL(clicked()), this, SLOT(textureForNewMaterial()));
    connect(selectButton, SIGNAL(clicked(bool)), widget, SLOT(close()));
    QPushButton* cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), widget, SLOT(close()));
    frameLayout->addWidget(selectButton);
    frameLayout->addWidget(cancelButton);

    frame->setLayout(frameLayout);
    layout->addWidget(frame);

    widget->setLayout(layout);
    widget->show();
}

void Editor::textureForNewMaterial() {
    Texture* selectedTexture = _listForNewMaterialDir[newMaterialList->selectedItems()[0]];
    //TODO: add shader too
    QString name = QInputDialog::getText(this, "Material Name", "Please name the new Material");
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString path = dialog.selectedFiles()[0];
    Shader* basicShader = Shader::createShader("basic shader", "basicShader");
    if (!name.isEmpty() && !path.isEmpty()) {
        Material::createMaterial(name.toStdString(), path.toStdString(), basicShader, selectedTexture);
        saveProjectMeta();
    }
}

void Editor::updateMaterialManager() {
    materialsList->clear();
    std::map<unsigned int, Material *> loadedMaterials = AssetManager<Material>::getLoadedAssets();
    for (std::pair<unsigned int, Material*> materialPair: loadedMaterials) {
        QListWidgetItem* item = new QListWidgetItem(materialPair.second->name.c_str());
        _listMaterialDir[item] = materialPair.second;
        materialsList->addItem(item);
    }
}

void Editor::materialSelected(QListWidgetItem *item) {
    std::cout << item->text().toStdString() << std::endl;
}

std::string removeExtension(const std::string &filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}
