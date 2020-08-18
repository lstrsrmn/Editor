#ifndef ENGINE_EDITOR_EDITORVIEW_H
#define ENGINE_EDITOR_EDITORVIEW_H

#include <QFormLayout>
#include <QLineEdit>
#include <string>
#include <QValidator>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <functional>
#include "EventHandler.h"

class EditorFunctions {
public:
    static void label(QFormLayout*, const QString&);
    static void textInput(QFormLayout*, const QString&, TextEventHandler*, const QString& = "");
    static void intInput(QFormLayout*, const QString&, IntEventHandler*, const QString& = "");
    static void floatInput(QFormLayout*, const QString&, const std::function<void(float)>&, const float, int = 4);
    static void floatInput(QFormLayout*, const QString&, float&, int = 4);
    static void filePathInput(QFormLayout*, const QString&, FileEventHandler*);
    static void buttonInput(QFormLayout*, const QString&, ButtonCallbackHandler*);

    template<typename T>
    static void dropdownInput(QFormLayout*, CallbackListener*, std::map<std::string, T*>);
private:
    EditorFunctions() = default;
};


template<typename T>
void EditorFunctions::dropdownInput(QFormLayout *layout, CallbackListener *listener, std::map<std::string, T*> dictionary) {
    QComboBox* dropdown = new QComboBox;
    for (std::pair<std::string, T*> kvp : dictionary) {
        dropdown->addItem(QString(kvp.first.c_str()));
    }
    layout->addWidget(dropdown);
    QObject::connect(dropdown, SIGNAL(textActivated(const QString&)), listener, SLOT(changed(const QString&)));
}


template<typename T>
struct EditorView {
};

#define CUSTOM_EDITOR(type) \
template<> \
struct EditorView<type> \

#define DISPLAY_EDITOR_VIEW(type) \
static inline void displayEditorView(type* object, QFormLayout* layout)

#endif //ENGINE_EDITOR_EDITORVIEW_H
