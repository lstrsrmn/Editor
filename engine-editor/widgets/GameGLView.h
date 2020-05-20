#ifndef ENGINE_EDITOR_GAMEGLVIEW_H
#define ENGINE_EDITOR_GAMEGLVIEW_H

#include <engine/Core.h>
#include <engine/Objects.h>
#include <QMainWindow>
#include <QOpenGLExtraFunctions>
#include <QtWidgets>

namespace Ui {
    class GameGLView;
}

class GameGLView : public QOpenGLWidget {
Q_OBJECT
public:
    explicit GameGLView(QWidget *parent = nullptr);
    ~GameGLView() override;

    void bindScene(Scene*);
signals:

public slots:

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    bool _initialised = false;
    QOpenGLContext *_context;
    Game* _game;
    Scene* _scene;
    Material* _material;
};

#endif //ENGINE_EDITOR_GAMEGLVIEW_H
