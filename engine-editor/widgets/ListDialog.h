//
// Created by lstrsrmn on 26/05/2020.
//

#ifndef ENGINE_EDITOR_LISTDIALOG_H
#define ENGINE_EDITOR_LISTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <string>
#include <map>
#include <engine/core/AssetManager.h>
#include <QEventLoop>

class ListDialogWidget : public QDialog {
Q_OBJECT
public:
    ListDialogWidget(std::vector<QListWidgetItem*>);
    QListWidgetItem* getResult();
private:
    QListWidget* list;
    QListWidgetItem* result;
private slots:
    void clicked();
};

template<typename T>
T* listSelectDialog();

template<typename T>
T *listSelectDialog() {
    std::map<QListWidgetItem*, T*> _dictionary;
    std::vector<QListWidgetItem*> widgetItems;
    std::map<unsigned int, T*> loadedAssets = AssetManager<T>::getLoadedAssets();
    for (std::pair<unsigned int, T*> pair: loadedAssets) {
        QListWidgetItem* item = new QListWidgetItem(pair.second->name.c_str());
        _dictionary[item] = pair.second;
        widgetItems.push_back(item);
    }
    ListDialogWidget* widget = new ListDialogWidget(widgetItems);
    widget->exec();
    if (widget->getResult() == nullptr)
        return nullptr;
    return _dictionary[widget->getResult()];
}

#endif //ENGINE_EDITOR_LISTDIALOG_H
