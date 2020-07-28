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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../../widgets/ProgramGLView.h"

QT_BEGIN_NAMESPACE

class Ui_Editor
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionClose;
    QAction *actionRecently_Closed;
    QAction *actionAdd_Object;
    QAction *actionAdd_Shader;
    QAction *actionAdd_Script;
    QAction *actionAdd_Object_2;
    QAction *actionNew_Object;
    QAction *actionMaterials;
    QAction *actionTextures;
    QAction *actionShaders;
    QAction *actionSave_Scene;
    QAction *actionNew_Scene;
    QAction *actionOpen_Scene;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QCommandLinkButton *runStopButton;
    QTabWidget *ViewPort;
    QWidget *Scene;
    QVBoxLayout *sceneVerticalLayout;
    ProgramGLView *programGLWidget;
    QWidget *Game;
    QVBoxLayout *gameVerticalLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuScene;
    QMenu *menuAssets;
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
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_7;
    QTreeWidget *hierarchyTree;
    QDockWidget *Project;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_8;
    QTreeWidget *projectTree;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *folderContents;

    void setupUi(QMainWindow *Editor)
    {
        if (Editor->objectName().isEmpty())
            Editor->setObjectName(QString::fromUtf8("Editor"));
        Editor->resize(800, 564);
        actionNew_Project = new QAction(Editor);
        actionNew_Project->setObjectName(QString::fromUtf8("actionNew_Project"));
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
        actionMaterials = new QAction(Editor);
        actionMaterials->setObjectName(QString::fromUtf8("actionMaterials"));
        actionTextures = new QAction(Editor);
        actionTextures->setObjectName(QString::fromUtf8("actionTextures"));
        actionShaders = new QAction(Editor);
        actionShaders->setObjectName(QString::fromUtf8("actionShaders"));
        actionSave_Scene = new QAction(Editor);
        actionSave_Scene->setObjectName(QString::fromUtf8("actionSave_Scene"));
        actionNew_Scene = new QAction(Editor);
        actionNew_Scene->setObjectName(QString::fromUtf8("actionNew_Scene"));
        actionOpen_Scene = new QAction(Editor);
        actionOpen_Scene->setObjectName(QString::fromUtf8("actionOpen_Scene"));
        centralwidget = new QWidget(Editor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        runStopButton = new QCommandLinkButton(centralwidget);
        runStopButton->setObjectName(QString::fromUtf8("runStopButton"));
        runStopButton->setEnabled(false);
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
        sceneVerticalLayout = new QVBoxLayout(Scene);
        sceneVerticalLayout->setObjectName(QString::fromUtf8("sceneVerticalLayout"));
        programGLWidget = new ProgramGLView(Scene);
        programGLWidget->setObjectName(QString::fromUtf8("programGLWidget"));

        sceneVerticalLayout->addWidget(programGLWidget);

        ViewPort->addTab(Scene, QString());
        Game = new QWidget();
        Game->setObjectName(QString::fromUtf8("Game"));
        gameVerticalLayout = new QVBoxLayout(Game);
        gameVerticalLayout->setObjectName(QString::fromUtf8("gameVerticalLayout"));
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
        menuAssets = new QMenu(menubar);
        menuAssets->setObjectName(QString::fromUtf8("menuAssets"));
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 146, 261));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        inspectorObjects = new QToolBox(scrollAreaWidgetContents);
        inspectorObjects->setObjectName(QString::fromUtf8("inspectorObjects"));
        inspectorObjects->setEnabled(false);
        Transform = new QWidget();
        Transform->setObjectName(QString::fromUtf8("Transform"));
        Transform->setGeometry(QRect(0, 0, 128, 212));
        inspectorObjects->addItem(Transform, QString::fromUtf8("Transform"));

        verticalLayout_6->addWidget(inspectorObjects);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(scrollArea);

        inspector->setWidget(inspectorContents);
        Editor->addDockWidget(Qt::RightDockWidgetArea, inspector);
        hierarchy = new QDockWidget(Editor);
        hierarchy->setObjectName(QString::fromUtf8("hierarchy"));
        hierarchy->setMinimumSize(QSize(141, 183));
        hierarchy->setMaximumSize(QSize(384, 524287));
        hierarchy->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        hierarchy->setFeatures(QDockWidget::NoDockWidgetFeatures);
        hierarchyContents = new QWidget();
        hierarchyContents->setObjectName(QString::fromUtf8("hierarchyContents"));
        verticalLayout_4 = new QVBoxLayout(hierarchyContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_2 = new QScrollArea(hierarchyContents);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 274, 261));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        hierarchyTree = new QTreeWidget(scrollAreaWidgetContents_2);
        hierarchyTree->setObjectName(QString::fromUtf8("hierarchyTree"));
        hierarchyTree->setMinimumSize(QSize(123, 0));

        verticalLayout_7->addWidget(hierarchyTree);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(scrollArea_2);

        hierarchy->setWidget(hierarchyContents);
        Editor->addDockWidget(Qt::LeftDockWidgetArea, hierarchy);
        Project = new QDockWidget(Editor);
        Project->setObjectName(QString::fromUtf8("Project"));
        Project->setMinimumSize(QSize(240, 107));
        Project->setMaximumSize(QSize(524287, 241));
        Project->setStyleSheet(QString::fromUtf8("background-color: rgb(223, 223, 223);"));
        Project->setFeatures(QDockWidget::NoDockWidgetFeatures);
        Project->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea_4 = new QScrollArea(dockWidgetContents);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 386, 202));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        projectTree = new QTreeWidget(scrollAreaWidgetContents_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        projectTree->setHeaderItem(__qtreewidgetitem);
        projectTree->setObjectName(QString::fromUtf8("projectTree"));

        verticalLayout_8->addWidget(projectTree);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        horizontalLayout->addWidget(scrollArea_4);

        scrollArea_3 = new QScrollArea(dockWidgetContents);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 386, 202));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        folderContents = new QTableWidget(scrollAreaWidgetContents_3);
        if (folderContents->columnCount() < 3)
            folderContents->setColumnCount(3);
        folderContents->setObjectName(QString::fromUtf8("folderContents"));
        folderContents->setShowGrid(false);
        folderContents->setRowCount(0);
        folderContents->setColumnCount(3);
        folderContents->horizontalHeader()->setVisible(false);
        folderContents->horizontalHeader()->setHighlightSections(false);
        folderContents->verticalHeader()->setVisible(false);
        folderContents->verticalHeader()->setHighlightSections(false);

        horizontalLayout_2->addWidget(folderContents);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        horizontalLayout->addWidget(scrollArea_3);

        Project->setWidget(dockWidgetContents);
        Editor->addDockWidget(Qt::BottomDockWidgetArea, Project);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuScene->menuAction());
        menubar->addAction(menuAssets->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuScene->addAction(actionSave_Scene);
        menuScene->addAction(actionNew_Scene);
        menuScene->addAction(actionOpen_Scene);
        menuScene->addSeparator();
        menuScene->addAction(actionNew_Object);
        menuAssets->addAction(actionMaterials);
        menuAssets->addAction(actionTextures);
        menuAssets->addAction(actionShaders);

        retranslateUi(Editor);

        ViewPort->setCurrentIndex(0);
        inspectorObjects->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Editor);
    } // setupUi

    void retranslateUi(QMainWindow *Editor)
    {
        Editor->setWindowTitle(QCoreApplication::translate("Editor", "MainWindow", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("Editor", "New Project", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("Editor", "Open Project", nullptr));
        actionClose->setText(QCoreApplication::translate("Editor", "Close", nullptr));
        actionRecently_Closed->setText(QCoreApplication::translate("Editor", "Recently Closed", nullptr));
        actionAdd_Object->setText(QCoreApplication::translate("Editor", "Add Object", nullptr));
        actionAdd_Shader->setText(QCoreApplication::translate("Editor", "Add Material", nullptr));
        actionAdd_Script->setText(QCoreApplication::translate("Editor", "Add Script", nullptr));
        actionAdd_Object_2->setText(QCoreApplication::translate("Editor", "Add Object", nullptr));
        actionNew_Object->setText(QCoreApplication::translate("Editor", "New Object", nullptr));
        actionMaterials->setText(QCoreApplication::translate("Editor", "Materials", nullptr));
        actionTextures->setText(QCoreApplication::translate("Editor", "Textures", nullptr));
        actionShaders->setText(QCoreApplication::translate("Editor", "Shaders", nullptr));
        actionSave_Scene->setText(QCoreApplication::translate("Editor", "Save Scene", nullptr));
        actionNew_Scene->setText(QCoreApplication::translate("Editor", "New Scene", nullptr));
        actionOpen_Scene->setText(QCoreApplication::translate("Editor", "Open Scene", nullptr));
        runStopButton->setText(QCoreApplication::translate("Editor", "Run", nullptr));
        ViewPort->setTabText(ViewPort->indexOf(Scene), QCoreApplication::translate("Editor", "Scene", nullptr));
#if QT_CONFIG(tooltip)
        Game->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        ViewPort->setTabText(ViewPort->indexOf(Game), QCoreApplication::translate("Editor", "Game", nullptr));
        menuFile->setTitle(QCoreApplication::translate("Editor", "File", nullptr));
        menuScene->setTitle(QCoreApplication::translate("Editor", "Scene", nullptr));
        menuAssets->setTitle(QCoreApplication::translate("Editor", "Assets", nullptr));
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
