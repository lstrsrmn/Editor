#ifndef EDITOR_H
#define EDITOR_H

#include <cstdio>
#include <map>
#include <QMainWindow>
#include <engine/game/Scene.h>
#include <engine/graphics/ModelImporter.h>
//#include "../widgets/GameGLView.h"

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
    Ui::Editor *ui;
    bool _gameRunning = false;
    std::map<QTreeWidgetItem*, GameObject*> _treeObjectDir;

private slots:
    void objectSelected(QTreeWidgetItem*, int);
    void test(bool);
    void viewPortChanged(int);
    void runButtonClicked();
    void loadScene();
};

#endif // EDITOR_H
