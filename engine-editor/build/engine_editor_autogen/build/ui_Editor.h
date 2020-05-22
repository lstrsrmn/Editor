/********************************************************************************
** Form generated from reading UI file 'Editor.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../../widgets/GameGLView.h"
#include "../../../widgets/SceneGLView.h"

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QAction *actionNew_Scene;
    QAction *actionNew_Project;
    QAction *actionOpen_Scene;
    QAction *actionOpen_Project;
    QAction *actionClose;
    QAction *actionRecently_Closed;
    QAction *actionAdd_Object;
    QAction *actionAdd_Shader;
    QAction *actionAdd_Script;
    QAction *actionAdd_Object_2;
    QAction *actionNew_Object;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *runStopButton;
    QTabWidget *ViewPort;
    QWidget *Scene;
    QVBoxLayout *verticalLayout_3;
    SceneGLView *sceneGLWidget;
    QWidget *Game;
    QVBoxLayout *verticalLayout_2;
    GameGLView *gameGLWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuScene;
    QDockWidget *inspector;
    QWidget *inspectorContents;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QToolBox *inspectorObjects;
    QWidget *Transform;
    QDockWidget *hierarchy;
    QWidget *hierarchyContents;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *hierarchyTree;
    QDockWidget *Project;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(800, 564);
        actionNew_Scene = new QAction(Editor);
        actionNew_Scene->setObjectName(QString::fromUtf8("actionNew_Scene"));
        actionNew_Project = new QAction(Editor);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
        actionOpen_Scene = new QAction(Editor);
        actionOpen_Scene->setObjectName(QString::fromUtf8("actionOpen_Scene"));
        actionOpen_Project = new QAction(Editor);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        actionClose = new QAction(Editor);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionRecently_Closed = new QAction(Editor);
        actionRecently_Closed->setObjectName(QString::fromUtf8("actionRecently_Closed"));
        actionAdd_Object = new QAction(Editor);
        actionAdd_Object->setObjectName(QString::fromUtf8("actionAdd_Object"));
        actionAdd_Shader = new QAction(Editor);
        actionAdd_Shader->setObjectName(QString::fromUtf8("actionAdd_Shader"));
        actionAdd_Script = new QAction(Editor);
        actionAdd_Script->setObjectName(QString::fromUtf8("actionAdd_Script"));
        actionAdd_Object_2 = new QAction(Editor);
        actionAdd_Object_2->setObjectName(QString::fromUtf8("actionAdd_Object_2"));
        actionNew_Object = new QAction(Editor);
        actionNew_Object->setObjectName(QString::fromUtf8("actionNew_Object"));
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        runStopButton = new QCommandLinkButton(centralwidget);
        runStopButton->setObjectName(QString::fromUtf8("runStopButton"));
        runStopButton->setCursor(QCursor(Qt::PointingHandCursor));
        runStopButton->setCheckable(false);

        verticalLayout->addWidget(runStopButton);

        ViewPort = new QTabWidget(centralwidget);
        ViewPort->setObjectName(QString::fromUtf8("ViewPort"));
        ViewPort->setStyleSheet(QString::fromUtf8("QFrame {\n"
"	border-color: rgb(0, 0, 0);\n"
"	border: 100px\n"
"}"));
        Scene = new QWidget();
        Scene->setObjectName(QString::fromUtf8("Scene"));
        verticalLayout_3 = new QVBoxLayout(Scene);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        sceneGLWidget = new SceneGLView(Scene);
        sceneGLWidget->setObjectName(QString::fromUtf8("sceneGLWidget"));

        verticalLayout_3->addWidget(sceneGLWidget);

        ViewPort->addTab(Scene, QString());
        Game = new QWidget();
        Game->setObjectName(QString::fromUtf8("Game"));
        verticalLayout_2 = new QVBoxLayout(Game);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gameGLWidget = new GameGLView(Game);
        gameGLWidget->setObjectName(QString::fromUtf8("gameGLWidget"));
        gameGLWidget->setEnabled(false);

        verticalLayout_2->addWidget(gameGLWidget);

        ViewPort->addTab(Game, QString());

        verticalLayout->addWidget(ViewPort);

        Editor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Editor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuScene = new QMenu(menubar);
        menuScene->setObjectName(QString::fromUtf8("menuScene"));
        Editor->setMenuBar(menubar);
        inspector = new QDockWidget(Editor);
        inspector->setObjectName(QString::fromUtf8("inspector"));
        inspector->setMinimumSize(QSize(166, 167));
        inspector->setMaximumSize(QSize(465, 524287));
        inspector->setAutoFillBackground(false);
        inspector->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        inspector->setFloating(false);
        inspector->setFeatures(QDockWidget::NoDockWidgetFeatures);
        inspectorContents = new QWidget();
        inspectorContents->setObjectName(QString::fromUtf8("inspectorContents"));
        verticalLayout_5 = new QVBoxLayout(inspectorContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        scrollArea = new QScrollArea(inspectorContents);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 146, 419));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        inspectorObjects = new QToolBox(scrollAreaWidgetContents);
        inspectorObjects->setObjectName(QString::fromUtf8("inspectorObjects"));
        inspectorObjects->setEnabled(false);
        Transform = new QWidget();
        Transform->setObjectName(QString::fromUtf8("Transform"));
        Transform->setGeometry(QRect(0, 0, 128, 370));
        inspectorObjects->addItem(Transform, QString::fromUtf8("Transform"));

        verticalLayout_6->addWidget(inspectorObjects);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(scrollArea);

        inspector->setWidget(inspectorContents);
        Editor->addDockWidget(Qt::RightDockWidgetArea, inspector);
        hierarchy = new QDockWidget(Editor);
        hierarchy->setObjectName(QString::fromUtf8("hierarchy"));
        hierarchy->setMinimumSize(QSize(141, 138));
        hierarchy->setMaximumSize(QSize(384, 524287));
        hierarchy->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        hierarchy->setFeatures(QDockWidget::NoDockWidgetFeatures);
        hierarchyContents = new QWidget();
        hierarchyContents->setObjectName(QString::fromUtf8("hierarchyContents"));
        verticalLayout_4 = new QVBoxLayout(hierarchyContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        hierarchyTree = new QTreeWidget(hierarchyContents);
        hierarchyTree->setObjectName(QString::fromUtf8("hierarchyTree"));
        hierarchyTree->setMinimumSize(QSize(123, 0));

        verticalLayout_4->addWidget(hierarchyTree);

        hierarchy->setWidget(hierarchyContents);
        Editor->addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
        Project = new QDockWidget(Editor);
        Project->setObjectName(QString::fromUtf8("Project"));
        Project->setMinimumSize(QSize(58, 83));
        Project->setMaximumSize(QSize(524287, 241));
        Project->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        Project->setFeatures(QDockWidget::NoDockWidgetFeatures);
        Project->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        Project->setWidget(dockWidgetContents);
        Editor->addDockWidget(Qt::BottomDockWidgetArea, Project);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuScene->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionNew_Scene);
        menuFile->addAction(actionOpen_Scene);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuScene->addAction(actionNew_Object);

        retranslateUi(Editor);

        ViewPort->setCurrentIndex(0);
        inspectorObjects->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QCoreApplication::translate("Editor", "MainWindow", nullptr));
        actionNew_Scene->setText(QCoreApplication::translate("Editor", "New Scene", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("Editor", "New Project", nullptr));
        actionOpen_Scene->setText(QCoreApplication::translate("Editor", "Open Scene", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("Editor", "Open Project", nullptr));
        actionClose->setText(QCoreApplication::translate("Editor", "Close", nullptr));
        actionRecently_Closed->setText(QCoreApplication::translate("Editor", "Recently Closed", nullptr));
        actionAdd_Object->setText(QCoreApplication::translate("Editor", "Add Object", nullptr));
        actionAdd_Shader->setText(QCoreApplication::translate("Editor", "Add Material", nullptr));
        actionAdd_Script->setText(QCoreApplication::translate("Editor", "Add Script", nullptr));
        actionAdd_Object_2->setText(QCoreApplication::translate("Editor", "Add Object", nullptr));
        actionNew_Object->setText(QCoreApplication::translate("Editor", "New Object", nullptr));
        runStopButton->setText(QCoreApplication::translate("Editor", "Run", nullptr));
        ViewPort->setTabText(ViewPort->indexOf(Scene), QCoreApplication::translate("Editor", "Scene", nullptr));
#if QT_CONFIG(tooltip)
        Game->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p>Test2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        gameGLWidget->setToolTip(QCoreApplication::translate("Editor", "<html><head/><body><p>Test1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ViewPort->setTabText(ViewPort->indexOf(Game), QCoreApplication::translate("Editor", "Game", nullptr));
        menuFile->setTitle(QCoreApplication::translate("Editor", "File", nullptr));
        menuScene->setTitle(QCoreApplication::translate("Editor", "Scene", nullptr));
        inspector->setWindowTitle(QCoreApplication::translate("Editor", "Inspector", nullptr));
        inspectorObjects->setItemText(inspectorObjects->indexOf(Transform), QCoreApplication::translate("Editor", "Transform", nullptr));
        hierarchy->setWindowTitle(QCoreApplication::translate("Editor", "Hierarchy", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = hierarchyTree->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Editor", "Scene", nullptr));
        Project->setWindowTitle(QCoreApplication::translate("Editor", "Project", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Editor: public Ui_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
