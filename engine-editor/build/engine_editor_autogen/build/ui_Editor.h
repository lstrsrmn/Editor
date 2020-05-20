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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
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
    QMenu *menuWindows;
    QDockWidget *inspector;
    QWidget *inspectorContents;
    QDockWidget *hierarchy;
    QWidget *hierarchyContents;
    QVBoxLayout *verticalLayout_4;
    QPushButton *loadButton;
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
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
        Editor->setMenuBar(menubar);
        inspector = new QDockWidget(Editor);
        inspector->setObjectName(QString::fromUtf8("inspector"));
        inspector->setMinimumSize(QSize(166, 35));
        inspector->setMaximumSize(QSize(465, 524287));
        inspector->setAutoFillBackground(false);
        inspector->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        inspector->setFloating(false);
        inspector->setFeatures(QDockWidget::NoDockWidgetFeatures);
        inspectorContents = new QWidget();
        inspectorContents->setObjectName(QString::fromUtf8("inspectorContents"));
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
        loadButton = new QPushButton(hierarchyContents);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout_4->addWidget(loadButton);

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
        menubar->addAction(menuWindows->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionNew_Scene);
        menuFile->addAction(actionOpen_Scene);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuWindows->addAction(actionRecently_Closed);

        retranslateUi(Editor);

        ViewPort->setCurrentIndex(0);


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
        menuWindows->setTitle(QCoreApplication::translate("Editor", "Windows", nullptr));
        inspector->setWindowTitle(QCoreApplication::translate("Editor", "Inspector", nullptr));
        hierarchy->setWindowTitle(QCoreApplication::translate("Editor", "Hierarchy", nullptr));
        loadButton->setText(QCoreApplication::translate("Editor", "Load Scene", nullptr));
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
