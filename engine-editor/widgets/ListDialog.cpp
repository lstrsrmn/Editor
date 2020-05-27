#include <iostream>
#include "ListDialog.h"

ListDialogWidget::ListDialogWidget(std::vector<QListWidgetItem*> items) {
    QVBoxLayout* layout = new QVBoxLayout;
    setWindowTitle("Select");

    list = new QListWidget;
    for (QListWidgetItem* item : items) {
        list->addItem(item);
    }
    layout->addWidget(list);

    QFrame* frame = new QFrame;
    QHBoxLayout* frameLayout = new QHBoxLayout;
    QPushButton* selectButton = new QPushButton("Select");
    connect(selectButton, SIGNAL(clicked()), this, SLOT(clicked()));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(close()));
    QPushButton* cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    frameLayout->addWidget(selectButton);
    frameLayout->addWidget(cancelButton);
    frame->setLayout(frameLayout);

    layout->addWidget(frame);
    setLayout(layout);
    setWindowModality(Qt::ApplicationModal);
    show();
}

void ListDialogWidget::clicked() {
    if (list->selectedItems().length() == 0)
        return;
    result = list->selectedItems()[0];
}

QListWidgetItem *ListDialogWidget::getResult() {
    return result;
}



