#ifndef ENGINE_EDITOR_EDITORVIEW_H
#define ENGINE_EDITOR_EDITORVIEW_H

#include <QFormLayout>
#include <QLineEdit>
#include <string>
#include <QValidator>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include "EventHandler.h"

class EditorFunctions {
public:
    static void label(QFormLayout*, const QString&);
    static void textInput(QFormLayout*, const QString&, TextEventHandler*, const QString& = "");
    static void intInput(QFormLayout*, const QString&, IntEventHandler*, const QString& = "");
    static void floatInput(QFormLayout*, const QString&, FloatEventHandler*, const QString& = "", int = 4);
    static void buttonInput(QFormLayout*, const QString&, ButtonEventHandler*);
    static void filePathInput(QFormLayout*, const QString&, FileEventHandler*);
private:
    EditorFunctions() = default;
};

template<typename T>
struct EditorView {
};

#define CUSTOM_EDITOR(type) \
template<> \
struct EditorView<type> \

#define DISPLAY_EDITOR_VIEW(type) \
static inline void displayEditorView(type* object, QFormLayout* layout)

#endif //ENGINE_EDITOR_EDITORVIEW_H
