//
// Created by lstrsrmn on 23/05/2020.
//

#ifndef ENGINE_EDITOR_EVENTHANDLER_H
#define ENGINE_EDITOR_EVENTHANDLER_H

#include <QWidget>
#include <QObject>
#include <QtWidgets/QFileDialog>

typedef void (*buttonPressedCallBack)();

class FloatEventHandler : public QObject {
Q_OBJECT
public:
    explicit FloatEventHandler(float *);

private slots:

    void changed(const QString &);

private:
    float *_var;
};

class IntEventHandler : public QObject {
Q_OBJECT
public:
    explicit IntEventHandler(int *);

private slots:

    void changed(const QString &);

private:
    int *_var;
};

class TextEventHandler : public QObject {
Q_OBJECT
public:
    explicit TextEventHandler(QString *);

private slots:

    void changed(const QString &);

private:
    QString *_var;
};

class FileEventHandler : public QObject {
Q_OBJECT
public:
    explicit FileEventHandler(QString *);

private slots:

    void openFileDialog();

private:
    QString *_path;
};

class CallbackListener : public QObject {
Q_OBJECT
public:
    explicit CallbackListener(std::function<void(const QString &)>);

    template<typename T>
    static std::function<void(const QString &)> createCallback(T *, void(T::*)(const QString &));

private:
    std::function<void(const QString &)> _callback;
private slots:

    void changed(const QString &);
};

template<typename T>
std::function<void(const QString &)>
CallbackListener::createCallback(T *listener, void(T::*callback)(const QString &)) {
    return std::bind(callback, listener, std::placeholders::_1);
}


class ButtonCallbackHandler : public QObject {
Q_OBJECT
public:
    explicit ButtonCallbackHandler(std::function<void()>);

    template<typename T>
    static std::function<void()> createCallback(T*, void(T::*)());

private:
    std::function<void()> _callback;
private slots:
    void clicked();
};

template<typename T>
std::function<void()> ButtonCallbackHandler::createCallback(T *listener, void(T::*callback)()) {
    return std::bind(callback, listener);
}
#endif //ENGINE_EDITOR_EVENTHANDLER_H
