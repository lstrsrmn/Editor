//
// Created by lstrsrmn on 23/05/2020.
//

#ifndef ENGINE_EDITOR_EVENTHANDLER_H
#define ENGINE_EDITOR_EVENTHANDLER_H

#include <QWidget>
#include <QObject>
#include <QtWidgets/QFileDialog>

typedef void (*buttonPressedCallBack)();
typedef void (*updateCallBack)();

class ButtonEventHandler: public QObject {
Q_OBJECT
public:
    explicit ButtonEventHandler(buttonPressedCallBack);
private slots:
    void clicked();
};

class FloatEventHandler: public QObject {
Q_OBJECT
public:
    explicit FloatEventHandler(float*);
private slots:
    void changed(const QString&);
private:
    float* _var;
};

class IntEventHandler: public QObject {
Q_OBJECT
public:
    explicit IntEventHandler(int*);
private slots:
    void changed(const QString&);
private:
    int* _var;
};

class TextEventHandler: public QObject {
Q_OBJECT
public:
    explicit TextEventHandler(QString*);
private slots:
    void changed(const QString&);
private:
    QString* _var;
};

class FileEventHandler: public QObject {
Q_OBJECT
public:
    explicit FileEventHandler(QString*);
private slots:
    void openFileDialog();
private:
    QString* _path;
};

template<typename T>
class UpdateEventHandler: public ButtonEventHandler{
public:
    explicit UpdateEventHandler(T);
private:
    void clicked();
private:
    T _object;
};

#endif //ENGINE_EDITOR_EVENTHANDLER_H
