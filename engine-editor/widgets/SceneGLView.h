//
// Created by lstrsrmn on 19/05/2020.
//

#ifndef ENGINE_EDITOR_SCENEGLVIEW_H
#define ENGINE_EDITOR_SCENEGLVIEW_H

#include <engine/Core.h>
#include <engine/Objects.h>
#include <QMainWindow>
#include <QOpenGLExtraFunctions>
#include <QtWidgets>


namespace Ui {
        class SceneGLView;
}

class SceneGLView: public QOpenGLWidget {
Q_OBJECT
public:
    explicit  SceneGLView(QWidget *parent = nullptr);
    ~SceneGLView() override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
signals:

private slots:

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    QPoint _mouseStartPos;
    bool _pan = false;
    bool _orbit = false;
    SceneView* _sceneView;
    Scene* _scene;
    Material* _material;
};


#endif //ENGINE_EDITOR_SCENEGLVIEW_H
