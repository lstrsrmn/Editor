#ifndef EDITOR_H
#define EDITOR_H

#include <cstdio>
#include <QMainWindow>
#include <engine/game/Scene.h>
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

private slots:
    void viewPortChanged(int);
    void runButtonClicked();
    void loadScene();
};

#endif // EDITOR_H
