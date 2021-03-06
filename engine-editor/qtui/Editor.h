#ifndef EDITOR_H
#define EDITOR_H

#include <cstdio>
#include <map>
#include <QMainWindow>
#include <engine/game/Scene.h>
#include <engine/graphics/ModelImporter.h>
#include <engine/editor/EditorView.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <nlohmann/json.hpp>
#include <engine/graphics/Texture.h>
#include <engine/graphics/Material.h>
#include "../widgets/ListDialog.h"
#include "../widgets/ProgramGLView.h"

namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:

    explicit Editor(QWidget *parent = nullptr);
    virtual ~Editor();
    void startup();

private:
//    ProgramGLView* _glViewCanvas;
    QListWidget* texturesList;
    QListWidget* materialsList;
    QListWidget* shadersList;
    void saveProjectMeta();
    void loadObject(const std::filesystem::path&);
    std::filesystem::path folderPath;
    GameObject* _selectedObject;
    Texture* _selectedTexture;
    Material* _selectedMaterial;
    Scene* _selectedScene;
    Ui::Editor *ui;
    bool _gameRunning = false;
    std::map<QTreeWidgetItem*, GameObject*> _treeObjectDir;
    std::map<QListWidgetItem*, Texture*> _listTextureDir;
    std::map<QListWidgetItem*, Shader*> _listShaderDir;
    std::map<QListWidgetItem*, Material*> _listMaterialDir;
    void recurseProjectTree(const std::string&, QTreeWidgetItem*);
    std::filesystem::path projectDir = "/home/lstrsrmn/Game-Engine-Projects/Test-Project";
    void recurseSceneHierarchy(GameObject*, QTreeWidgetItem*);

private slots:
    void openScene(bool = false);
    void newScene(bool = false);
    void saveScene(bool = false);
    void createMaterial();
    void updateMaterialManager();
    void materialSelected(QListWidgetItem*);
    void deleteShader(bool = false);
    void renameShader(bool = false);
    void shaderMenu(const QPoint &point);
    void createShaderFromFile();
    void updateShaderManager();
    void changeTextureName();
    void textureSelected(QListWidgetItem*);
    void createTextureFromFile();
    void updateTextureManager();
    void shaderManager(bool = false);
    void materialManager(bool = false);
    void textureManager(bool = false);
    void loadProject(bool = false);
    void newProject(bool = false);
    void setSceneViewFocus(bool = false);
    void deleteObject(bool = false);
    void renameObject(bool = false);
    void hierarchyMenu(const QPoint&);
    void loadTableItem(QTableWidgetItem*);
    void objectSelected(QTreeWidgetItem*, int);
    void loadObject(bool = false);
    void viewPortChanged(int);
    void runButtonClicked();
    void loadScene();
    void updateProject();
    void updateOpenFolder(QTreeWidgetItem*, int);
};

#endif // EDITOR_H
