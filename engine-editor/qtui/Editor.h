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

const std::string projectDir = "/home/lstrsrmn/Game-Engine-Projects/Test-Project";
namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:

    explicit Editor(QWidget *parent = nullptr);
    virtual ~Editor();

private:
    void createTexture(const std::string&, const std::string&);
    QFormLayout* currentTexturesLayout;
    QListWidget* texturesList;
    QListWidget* materialsList;
    QListWidget* newMaterialList;
    void saveProjectMeta();
    void loadObject(const std::string&);
    std::string folderPath;
    GameObject* _selectedObject;
    Texture* _selectedTexture;
    Ui::Editor *ui;
    bool _gameRunning = false;
    std::map<QTreeWidgetItem*, GameObject*> _treeObjectDir;
    std::map<QListWidgetItem*, Texture*> _listTextureDir;
    std::map<QListWidgetItem*, Texture*> _listForNewMaterialDir;
    std::map<QListWidgetItem*, Material*> _listMaterialDir;
    void recurseProjectTree(const std::string&, QTreeWidgetItem*);

private slots:
    void materialSelected(QListWidgetItem*);
    void updateMaterialManager();
    void textureForNewMaterial();
    void createMaterial();
    void materialManager(bool);
    void textureSelected(QListWidgetItem*);
    void deleteTexture();
    void createTextureFromFile();
    void updateTextureManager();
    void textureManager(bool);
    void loadProject(bool);
    void newProject(bool);
    void setSceneViewFocus(bool);
    void deleteObject(bool);
    void renameObject(bool);
    void hierarchyMenu(const QPoint&);
    void loadTableItem(QTableWidgetItem*);
    void objectSelected(QTreeWidgetItem*, int);
    void loadObject(bool);
    void viewPortChanged(int);
    void runButtonClicked();
    void loadScene();
    void updateProject();
    void updateOpenFolder(QTreeWidgetItem*, int);
};
static std::string removeExtension(const std::string&);

#endif // EDITOR_H
