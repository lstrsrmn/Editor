#include "Editor.h"
#include "../build/ui_Editor.h"

std::string projectDir = "/home/lstrsrmn/Game-Engine-Projects/Test-Project";
//std::string projectDir = "";

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
    connect(ui->actionShaders, SIGNAL(triggered(bool)), this, SLOT(shaderManager(bool)));
    connect(ui->actionSave_Scene, SIGNAL(triggered(bool)), this, SLOT(saveScene(bool)));
    connect(ui->actionNew_Scene, SIGNAL(triggered(bool)), this, SLOT(newScene(bool)));
    connect(ui->actionOpen_Scene, SIGNAL(triggered(bool)), this, SLOT(openScene(bool)));
    //TODO: then make game run scene, then make scenes savable
}

Editor::~Editor() {
    delete ui;
}

void Editor::startup() {
//    for (QObject *widget: ui->Scene->children()) {
//        delete widget;
//    }
//    for (QObject *widget: ui->Game->children()) {
//        delete widget;
//    }
//    _glViewCanvas = new ProgramGLView(ui->Scene);

    QWidget *window = new QWidget;
    window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window->size(),
                                            QGuiApplication::screens()[0]->geometry()));
    window->setAttribute(Qt::WA_DeleteOnClose, true);
    QVBoxLayout *layout = new QVBoxLayout;

    QImageReader reader("res/titlePage.png");
    QImage image = reader.read();
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(image));
    layout->addWidget(imageLabel);

    QFrame *frame = new QFrame;
    QHBoxLayout *frameLayout = new QHBoxLayout;
    QPushButton *newButton = new QPushButton("New Project");
    connect(newButton, SIGNAL(clicked()), this, SLOT(newProject()));
    connect(newButton, SIGNAL(clicked()), window, SLOT(close()));
    QPushButton *loadButton = new QPushButton("Load Project");
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadProject()));
    connect(loadButton, SIGNAL(clicked()), window, SLOT(close()));
    frameLayout->addWidget(newButton);
    frameLayout->addWidget(loadButton);
    frame->setLayout(frameLayout);
    layout->addWidget(frame);

    window->setLayout(layout);
    window->setWindowModality(Qt::ApplicationModal);
    window->show();
}

void Editor::runButtonClicked() {
    _gameRunning = !_gameRunning;
    ui->programGLWidget->changeGameEnabled(_gameRunning);
    if (_gameRunning) {
        ui->runStopButton->setText("Stop");
    } else {
        ui->runStopButton->setText("Run");
    }
}

void Editor::loadScene() {
    //TODO: make this work properly
    _selectedScene = SceneView::instance()->getCurrentScene();
    ui->hierarchyTree->clear();
    _treeObjectDir.clear();
    ui->hierarchyTree->setHeaderLabel(_selectedScene->getName());
    if (_selectedScene->getCamera() != nullptr) {
        QTreeWidgetItem* node = new QTreeWidgetItem(ui->hierarchyTree->invisibleRootItem());
        node->setText(0, "Camera");
    }
    {
        QTreeWidgetItem *node = new QTreeWidgetItem(ui->hierarchyTree->invisibleRootItem());
        node->setText(0, "Directional Light");
    }
    for (GameObject *object : _selectedScene->getObjects()) {
        QTreeWidgetItem *node = new QTreeWidgetItem(ui->hierarchyTree->invisibleRootItem());
        node->setText(0, object->getName());
        _treeObjectDir[node] = object;
    }
    ui->programGLWidget->updateSize();
}

void Editor::viewPortChanged(int newViewPort) {
    if (newViewPort == 0) {
        ui->runStopButton->setDisabled(true);
        ui->runStopButton->setText("Run");
        _gameRunning = false;
        ui->programGLWidget->setParent(ui->Scene);
        ui->sceneVerticalLayout->addWidget(ui->programGLWidget);
        ui->programGLWidget->changeViewPort(SCENE);
        ui->programGLWidget->setFocus();
    }
    else if (newViewPort == 1) {
        ui->runStopButton->setDisabled(false);
        ui->runStopButton->setText("Run");
        _gameRunning = false;
        ui->programGLWidget->setParent(ui->Game);
        ui->gameVerticalLayout->addWidget(ui->programGLWidget);
        ui->programGLWidget->changeViewPort(GAME);
        ui->programGLWidget->setFocus();
    }
}

void Editor::loadObject(bool) {
    QFileDialog dialog;
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString filePath = dialog.selectedFiles()[0];
    loadObject(filePath.toStdString());
}

void Editor::loadObject(const std::string &filePath) {
    const std::filesystem::path path = filePath;
    std::string fileName = removeExtension(path.filename().string());
    Scene *scene = SceneView::instance()->getCurrentScene();
    ModelMeshData input = loadModel(filePath);
    Material *material = listSelectDialog<Material>();
    if (material == nullptr)
        return;
    GameObject *newObject = scene->createGameObject();
    QString name = QInputDialog::getText(this, "Object name", "Please input object name");
    if (name.isEmpty())
        newObject->setName("new Object");
    else
        newObject->setName(name);
    MeshRenderer *renderer = new MeshRenderer(material, input);
    newObject->addComponent(renderer);
    loadScene();

    saveProjectMeta();
}

void Editor::objectSelected(QTreeWidgetItem *selectedWidget, int) {
    ui->inspectorObjects->setEnabled(true);

    if (selectedWidget->text(0) == "Camera") {
        QWidget *camera = ui->inspectorObjects->widget(0);
        for (QObject* widget : camera->children())
            delete widget;
        QFrame *cFrame = new QFrame(camera);
        QFormLayout *cLayout = new QFormLayout;
        EditorView<Camera>::displayEditorView(_selectedScene->getCamera(), cLayout);
        cFrame->setLayout(cLayout);
        cFrame->show();
        return;
    }

    if (selectedWidget->text(0) == "Directional Light") {
        return;
    }

    _selectedObject = _treeObjectDir[selectedWidget];

    for (int i = 0; i < ui->inspectorObjects->count() - 1; i++)
        ui->inspectorObjects->removeItem(1);
    for (Component *component: _selectedObject->getComponents()) {
        QWidget *node = new QWidget();
        QFrame* frame = new QFrame(node);
        ui->inspectorObjects->addItem(node, component->componentName().c_str());
        QFormLayout *layout = new QFormLayout;
        component->showInspector(layout);
        frame->setLayout(layout);
        frame->show();
    }

    QWidget *transform = ui->inspectorObjects->widget(0);
    QFrame *tFrame = new QFrame(transform);
    QFormLayout *tLayout = new QFormLayout;
    EditorView<Transform>::displayEditorView(&_selectedObject->getTransform(), tLayout);
    tFrame->setLayout(tLayout);
    tFrame->show();

}

void Editor::updateProject() {
    ui->projectTree->clear();
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
            std::cout << "Texture" << std::endl;
//            createTexture(name.toStdString(), filePath);
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
    ui->programGLWidget->setViewFocus(_selectedObject->getTransform().pos);
}

void Editor::newProject(bool) {
    QString filePath;
    QString previousPath;
    QFileDialog dialog;
    dialog.setWindowTitle("New Project");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    filePath = dialog.selectedFiles()[0];
    QString name = QInputDialog::getText(this, "New Project", "Please name the new Project");
    if (name.isEmpty())
        return;
    std::string path = filePath.toStdString() + "/" +name.toStdString();
    projectDir = path;
    mkdir((projectDir).c_str(), 0777);
    mkdir((projectDir + "/meta").c_str(), 0777);
    mkdir((projectDir + "/Assets").c_str(), 0777);
    mkdir((projectDir + "/Assets/Textures").c_str(), 0777);
    copyFile("res/textures/defaultDiffuse.jpg", projectDir + "/Assets/Textures/defaultTexture.jpg");
    Texture* texture = AssetManager<Texture>::createAsset("DefaultTexture", projectDir + "/Assets/Textures/defaultTexture.jpg");
    mkdir((projectDir + "/Assets/Shaders").c_str(), 0777);
    mkdir((projectDir + "/Assets/Shaders/basicShader").c_str(), 0777);
    copyFile("res/shaders/basicShader/basicShader.vs", projectDir + "/Assets/Shaders/basicShader/basicShader.vs");
    copyFile("res/shaders/basicShader/basicShader.fs", projectDir + "/Assets/Shaders/basicShader/basicShader.fs");
    Shader* shader = AssetManager<Shader>::createAsset("basicShader", projectDir + "/Assets/Shaders/basicShader");
    mkdir((projectDir + "/Assets/Materials").c_str(), 0777);
    Material::createMaterial("DefaultMaterial", projectDir + "/Assets/Materials", shader, texture);
    mkdir((projectDir + "/Assets/Models").c_str(), 0777);
    copyFile("res/models/default/Monkey.fbx", projectDir + "/Assets/Models/Monkey.fbx");
    copyFile("res/models/default/Plane.fbx", projectDir + "/Assets/Models/Plane.fbx");
    mkdir((projectDir + "/Assets/Scripts").c_str(), 0777);
    std::ofstream project(path + "meta/project.meta"), textures(path + "meta/textures.meta"),
    shaders(path + "meta/shaders.meta"), materials(path + "meta/materials.meta");
    mkdir((projectDir + "/Assets/Scenes").c_str(), 0777);
    std::cout << "working" << std::endl;
    saveProjectMeta();
    updateProject();
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
    QString filePath;
    QFileDialog dialog;
    dialog.setWindowTitle("Load Project");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
        dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    filePath = dialog.selectedFiles()[0];
    std::filesystem::path path = std::filesystem::path(filePath.toStdString() + "/meta");
    if (!std::filesystem::exists(path)) {
        std::cout << filePath.toStdString() << std::endl;
        QMessageBox error;
        error.setWindowTitle("Invalid path");
        error.setText(
                "The selected path doesn't meet requirements to be a project");
        error.exec();
        return;
    }

    projectDir = filePath.toStdString();
    const std::string projectMetaDir = projectDir + "/meta/";
    std::ifstream projectMeta(projectMetaDir + "project.meta");
    nlohmann::json project;
    projectMeta >> project;
    projectMeta.close();
    AssetManager<Texture>::readAssetMeta(projectMetaDir + "textures.meta");
    AssetManager<Shader>::readAssetMeta(projectMetaDir + "shaders.meta");
    AssetManager<Material>::readAssetMeta(projectMetaDir + "materials.meta");
    updateProject();
}

void Editor::textureManager(bool) {
    QWidget *manager = new QWidget();
    manager->setAttribute(Qt::WA_DeleteOnClose, true);
    QHBoxLayout *managerLayout = new QHBoxLayout();
    manager->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, manager->size(),
                                             QGuiApplication::screens()[0]->geometry()));
    manager->setWindowTitle("Texture Manager");
    texturesList = new QListWidget;
    texturesList->setAttribute(Qt::WA_DeleteOnClose, false);
    connect(texturesList, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
            SLOT(textureSelected(QListWidgetItem * )));
    updateTextureManager();
    managerLayout->addWidget(texturesList);
    texturesList->setParent(manager);

    QFrame *newTextures = new QFrame();
    QFormLayout *newTexturesLayout = new QFormLayout();
    QPushButton *newTexture = new QPushButton("Create new Texture");
    connect(newTexture, SIGNAL(clicked()), this, SLOT(createTextureFromFile()));
    newTexturesLayout->addRow(newTexture);

    newTextures->setLayout(newTexturesLayout);
    managerLayout->addWidget(newTextures);
    manager->setLayout(managerLayout);
    manager->setWindowModality(Qt::ApplicationModal);
    manager->show();
}

void Editor::updateTextureManager() {
    texturesList->clear();
    std::map<unsigned int, Texture *> loadedTextures = AssetManager<Texture>::getLoadedAssets();
    for (std::pair<unsigned int, Texture *> texturePair: loadedTextures) {
        QListWidgetItem *item = new QListWidgetItem(texturePair.second->name.c_str());
        _listTextureDir[item] = texturePair.second;
        texturesList->addItem(item);
    }
}


void Editor::createTextureFromFile() {
    QFileDialog dialog;
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString filePath = dialog.selectedFiles()[0];
    if (!filePath.isEmpty()) {
        QString name = QInputDialog::getText(this, "Create Texture", "Please input Texture name.");
        if (!name.isEmpty()) {
            Texture::createTexture(name.toStdString(), filePath.toStdString());
            saveProjectMeta();
            updateTextureManager();
        }
    }
}

void Editor::textureSelected(QListWidgetItem *item) {
    _selectedTexture = _listTextureDir[item];
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout();

    QImageReader *reader = new QImageReader(_selectedTexture->getFilePath().c_str());
    const QImage image = reader->read();
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(image.scaled(512, 512)));
    layout->addWidget(imageLabel);

    QFrame *buttons = new QFrame;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    QPushButton *nameButton = new QPushButton("Change Name");
    connect(nameButton, SIGNAL(clicked()), this, SLOT(changeTextureName()));
    QPushButton *deleteButton = new QPushButton("Delete");
    buttonsLayout->addWidget(nameButton);
    buttonsLayout->addWidget(deleteButton);
    buttons->setLayout(buttonsLayout);
    layout->addWidget(buttons);

    window->setLayout(layout);
    window->setWindowModality(Qt::ApplicationModal);
    window->show();
}

void Editor::changeTextureName() {
    QString newName = QInputDialog::getText(this, "Texture Name", "input new Texture name");
    _selectedTexture->name = newName.toStdString();
    saveProjectMeta();
    updateTextureManager();
}

void Editor::shaderManager(bool) {
    QWidget *window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose, true);
    QHBoxLayout *managerLayout = new QHBoxLayout();
    window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window->size(),
                                            QGuiApplication::screens()[0]->geometry()));
    window->setWindowTitle("Shader Manager");
    shadersList = new QListWidget;
    shadersList->setContextMenuPolicy(Qt::CustomContextMenu);
    shadersList->setAttribute(Qt::WA_DeleteOnClose, false);
    connect(shadersList, SIGNAL(customContextMenuRequested(const QPoint&)), this,
            SLOT(shaderMenu(const QPoint&)));
    updateShaderManager();
    managerLayout->addWidget(shadersList);
    shadersList->setParent(window);

    QFrame *newShaders = new QFrame();
    QFormLayout *newShadersLayout = new QFormLayout();
    QPushButton *newShader = new QPushButton("Create new Shader");
    connect(newShader, SIGNAL(clicked()), this, SLOT(createShaderFromFile()));
    newShadersLayout->addRow(newShader);

    newShaders->setLayout(newShadersLayout);
    managerLayout->addWidget(newShaders);
    window->setLayout(managerLayout);
    window->setWindowModality(Qt::ApplicationModal);
    window->show();
}

void Editor::updateShaderManager() {
    shadersList->clear();
    std::map<unsigned int, Shader *> loadedShaders = AssetManager<Shader>::getLoadedAssets();
    for (std::pair<unsigned int, Shader *> pair: loadedShaders) {
        QListWidgetItem *item = new QListWidgetItem(pair.second->name.c_str());
        _listShaderDir[item] = pair.second;
        shadersList->addItem(item);
    }
}

void Editor::createShaderFromFile() {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString filePath = dialog.selectedFiles()[0];
    if (!filePath.isEmpty()) {
        QString name = QInputDialog::getText(this, "Create Shader", "Please input Shader name.");
        if (!name.isEmpty()) {
            AssetManager<Shader>::createAsset(name.toStdString(), filePath.toStdString());
            saveProjectMeta();
            updateShaderManager();
        }
    }
}

void Editor::shaderMenu(const QPoint &point) {
    QListWidgetItem *clicked = shadersList->itemAt(point);
    if (clicked != nullptr) {
        shadersList->clearSelection();
        clicked->setSelected(true);
        QMenu *menu = new QMenu("menu");

        // Rename
        QAction *renamed = new QAction();
        renamed->setText("Rename");
        menu->addAction(renamed);
        connect(renamed, SIGNAL(triggered(bool)), this, SLOT(renameShader(bool)));
        menu->popup(QCursor::pos());

        // Delete
        QAction *deleteObject = new QAction();
        deleteObject->setText("Delete");
        menu->addAction(deleteObject);
        connect(deleteObject, SIGNAL(triggered(bool)), this, SLOT(deleteShader(bool)));
    }
}

void Editor::deleteShader(bool) {
//    QListWidgetItem *item = shadersList->selectedItems()[0];

}

void Editor::renameShader(bool) {
    QListWidgetItem *item = shadersList->selectedItems()[0];
    Shader *shader = _listShaderDir[item];
    QString name = QInputDialog::getText(this, "Shader Name", "Input Shader name");
    if (!name.isEmpty()) {
        shader->name = name.toStdString();
        saveProjectMeta();
        updateShaderManager();
    }
}

void Editor::materialManager(bool) {
    QWidget *window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose, true);
    QHBoxLayout *managerLayout = new QHBoxLayout();
    window->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, window->size(),
                                            QGuiApplication::screens()[0]->geometry()));
    window->setWindowTitle("Material Manager");
    materialsList = new QListWidget;
    materialsList->setAttribute(Qt::WA_DeleteOnClose, false);
    connect(materialsList, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
            SLOT(materialSelected(QListWidgetItem * )));
    updateMaterialManager();
    managerLayout->addWidget(materialsList);
    materialsList->setParent(window);

    QFrame *newMaterials = new QFrame();
    QFormLayout *newMaterialsLayout = new QFormLayout();
    QPushButton *newMaterial = new QPushButton("Create new Material");
    connect(newMaterial, SIGNAL(clicked()), this, SLOT(createMaterial()));
    newMaterialsLayout->addRow(newMaterial);

    newMaterials->setLayout(newMaterialsLayout);
    managerLayout->addWidget(newMaterials);
    window->setLayout(managerLayout);
    window->setWindowModality(Qt::ApplicationModal);
    window->show();
}

void Editor::updateMaterialManager() {
    materialsList->clear();
    std::map<unsigned int, Material *> loadedMaterials = AssetManager<Material>::getLoadedAssets();
    for (std::pair<unsigned int, Material *> pair: loadedMaterials) {
        QListWidgetItem *item = new QListWidgetItem(pair.second->name.c_str());
        _listMaterialDir[item] = pair.second;
        materialsList->addItem(item);
    }
}

void Editor::createMaterial() {
    Texture *texture = listSelectDialog<Texture>();
    if (texture == nullptr)
        return;
    Shader *shader = listSelectDialog<Shader>();
    if (shader == nullptr)
        return;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString filePath = dialog.selectedFiles()[0];
    if (filePath.isEmpty())
        return;
    QString name = QInputDialog::getText(this, "Material Name", "Choose new Material's name");
    if (name.isEmpty())
        return;
    Material::createMaterial(name.toStdString(), filePath.toStdString(), shader, texture);
    saveProjectMeta();
    updateMaterialManager();
}

void Editor::materialSelected(QListWidgetItem *) {

}

void Editor::saveScene(bool) {
    Scene* scene = SceneView::instance()->getCurrentScene();
    if (scene->_fileLocation == "") {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly, true);
        dialog.setOption(QFileDialog::DontResolveSymlinks, true);
        dialog.setOption(QFileDialog::DontUseNativeDialog, true);
        dialog.exec();
        scene->_fileLocation = dialog.selectedFiles()[0].toStdString();
    }
    scene->serializeToJSON();
}

void Editor::newScene(bool) {
    QFileDialog dialog;
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString result = dialog.selectedFiles()[0];
}

void Editor::openScene(bool) {
    QFileDialog dialog;
    dialog.setOption(QFileDialog::DontResolveSymlinks, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    dialog.exec();
    QString result = dialog.selectedFiles()[0];
    Scene* scene = Scene::deserializeFromJSON(result.toStdString());
    SceneView::instance()->addScene(scene);
    SceneView::instance()->setActive(scene->getId());
    Game::instance()->addScene(scene);
    Game::instance()->setActive(scene->getId());
    saveProjectMeta();
    loadScene();
    updateProject();
}




