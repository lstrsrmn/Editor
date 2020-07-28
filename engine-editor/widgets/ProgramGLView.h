//
// Created by lstrsrmn on 06/07/2020.
//

#ifndef ENGINE_EDITOR_PROGRAMGLVIEW_H
#define ENGINE_EDITOR_PROGRAMGLVIEW_H
#include <engine/Core.h>
#include <engine/Objects.h>
#include "ListDialog.h"
#include <QMainWindow>
#include <QOpenGLExtraFunctions>
#include <QtWidgets>

namespace Ui {
    class ProgramGLView;
}

enum ViewPortState {
    SCENE,
    GAME
};

class ProgramGLView : public QOpenGLWidget {

Q_OBJECT

public:
    explicit ProgramGLView(QWidget *parent = nullptr);
    void setViewFocus(glm::vec3 pos);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent*) override;
    void changeViewPort(ViewPortState);
    void changeGameEnabled(bool);
    void keyPressEvent(QKeyEvent*) override;
    void updateSize();
signals:

public slots:

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void bindScene(Scene *);
private:
    QPoint _mouseStartPos;
    bool _pan = false;
    bool _orbit = false;
    Scene* _scene;
    Game* _game;
    SceneView* _sceneView;
    ViewPortState _viewPortState = SCENE;
    bool _gameEnabled = false;
    bool _gameActive = false;
};


#endif //ENGINE_EDITOR_PROGRAMGLVIEW_H
