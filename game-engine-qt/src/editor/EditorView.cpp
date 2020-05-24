#include "../../include/engine/editor/EditorView.h"

void EditorFunctions::label(QFormLayout* layout, const QString &label) {
    layout->addRow(new QLabel(label));
}

void EditorFunctions::textInput(QFormLayout *layout, const QString &label ,TextEventHandler *handler, const QString& defaultText) {
    QLineEdit* inputBox = new QLineEdit();
    inputBox->setText(defaultText);
    layout->addRow(label, inputBox);
    QObject::connect(inputBox, SIGNAL(textChanged(const QString&)), handler, SLOT(changed(const QString&)));
}

void EditorFunctions::intInput(QFormLayout *layout, const QString &label, IntEventHandler* handler, const QString& defaultText) {
    QLineEdit* inputBox = new QLineEdit();
    inputBox->setValidator(new QIntValidator(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
    inputBox->setText(defaultText);
    layout->addRow(label, inputBox);
    QObject::connect(inputBox, SIGNAL(textChanged(const QString&)), handler, SLOT(changed(const QString&)));
}

void EditorFunctions::floatInput(QFormLayout *layout, const QString &label, FloatEventHandler* handler, const QString& defaultText, int decimals) {
    QLineEdit* inputBox = new QLineEdit();
    inputBox->setValidator(new QDoubleValidator(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), decimals));
    inputBox->setText(defaultText);
    layout->addRow(label, inputBox);
    QObject::connect(inputBox, SIGNAL(textChanged(const QString&)), handler, SLOT(changed(const QString&)));
}

void EditorFunctions::buttonInput(QFormLayout *layout, const QString &label, ButtonEventHandler* handler) {
    QPushButton* button = new QPushButton(label);
    layout->addRow(button);
    QObject::connect(button, SIGNAL(clicked()), handler, SLOT(clicked()));
}

void EditorFunctions::filePathInput(QFormLayout *layout, const QString &label, FileEventHandler* handler) {
    QPushButton* button = new QPushButton(label);
    layout->addRow(button);
    QObject::connect(button, SIGNAL(clicked()), handler, SLOT(openFileDialog()));
}

