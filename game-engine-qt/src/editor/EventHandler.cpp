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

FileEventHandler::FileEventHandler(QString *path) {
    _path = path;
}

void FileEventHandler::openFileDialog() {
    *_path = QFileDialog::getOpenFileName();
}

CallbackListener::CallbackListener(std::function<void(const QString&)> callback) {
    _callback = callback;
}

void CallbackListener::changed(const QString &value) {
    _callback(value);
}

ButtonCallbackHandler::ButtonCallbackHandler(std::function<void()> callback) {
    _callback = callback;
}

void ButtonCallbackHandler::clicked() {
    _callback();
}

