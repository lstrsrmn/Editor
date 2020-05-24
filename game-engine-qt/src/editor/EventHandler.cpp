//
// Created by lstrsrmn on 23/05/2020.
//

#include "../../include/engine/editor/EventHandler.h"

FloatEventHandler::FloatEventHandler(float *value) {
    _var = value;
}

void FloatEventHandler::changed(const QString &value) {
    *_var = value.toFloat();
}

IntEventHandler::IntEventHandler(int *value) {
    _var = value;
}

void IntEventHandler::changed(const QString &value) {
    *_var = value.toInt();
}

TextEventHandler::TextEventHandler(QString *value) {
    _var = value;
}

void TextEventHandler::changed(const QString &value) {
    *_var = value;
}


void ButtonEventHandler::clicked() {

}

FileEventHandler::FileEventHandler(QString *path) {
    _path = path;
}

void FileEventHandler::openFileDialog() {
    *_path = QFileDialog::getOpenFileName();
}

template<typename T>
UpdateEventHandler<T>::UpdateEventHandler(T object) {
    _object = object;
}

template<typename T>
void UpdateEventHandler<T>::clicked() {
    _object->update();
}
