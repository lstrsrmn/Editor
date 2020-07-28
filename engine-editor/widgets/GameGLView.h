#ifndef ENGINE_EDITOR_GAMEGLVIEW_H
#define ENGINE_EDITOR_GAMEGLVIEW_H

#include <engine/Core.h>
#include <engine/Objects.h>
#include "ListDialog.h"
#include <QMainWindow>
#include <QOpenGLExtraFunctions>
#include <QtWidgets>

namespace Ui {
    class GameGLView;
}

class GameGLView : public QOpenGLWidget {
Q_OBJECT
public:
    friend class ContextController;
    explicit GameGLView(QWidget *parent = nullptr);
    ~GameGLView() override;
    void bindScene(Scene*);
    inline void init() {initializeGL();}
signals:

public slots:

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    Game* _game;
    Scene* _scene;
};

#endif //ENGINE_EDITOR_GAMEGLVIEW_H
