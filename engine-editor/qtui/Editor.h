#ifndef EDITOR_H
#define EDITOR_H

#include <cstdio>
#include <map>
#include <QMainWindow>
#include <engine/game/Scene.h>
#include <engine/graphics/ModelImporter.h>
#include <engine/editor/EditorView.h>
#include <filesystem>

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
    void loadObject(const std::string&);
    std::string folderPath;
    GameObject* _selectedObject;
    Ui::Editor *ui;
    bool _gameRunning = false;
    std::map<QTreeWidgetItem*, GameObject*> _treeObjectDir;
    void recurseProjectTree(const std::string&, QTreeWidgetItem*);

private slots:
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

static std::string removeExtention(const std::string&);

#endif // EDITOR_H
