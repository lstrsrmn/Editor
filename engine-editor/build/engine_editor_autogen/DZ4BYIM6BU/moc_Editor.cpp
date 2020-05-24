/****************************************************************************
** Meta object code from reading C++ file 'Editor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../qtui/Editor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Editor_t {
    QByteArrayData data[16];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Editor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Editor_t qt_meta_stringdata_Editor = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Editor"
QT_MOC_LITERAL(1, 7, 17), // "setSceneViewFocus"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "deleteObject"
QT_MOC_LITERAL(4, 39, 12), // "renameObject"
QT_MOC_LITERAL(5, 52, 13), // "hierarchyMenu"
QT_MOC_LITERAL(6, 66, 13), // "loadTableItem"
QT_MOC_LITERAL(7, 80, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(8, 98, 14), // "objectSelected"
QT_MOC_LITERAL(9, 113, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(10, 130, 10), // "loadObject"
QT_MOC_LITERAL(11, 141, 15), // "viewPortChanged"
QT_MOC_LITERAL(12, 157, 16), // "runButtonClicked"
QT_MOC_LITERAL(13, 174, 9), // "loadScene"
QT_MOC_LITERAL(14, 184, 13), // "updateProject"
QT_MOC_LITERAL(15, 198, 16) // "updateOpenFolder"

    },
    "Editor\0setSceneViewFocus\0\0deleteObject\0"
    "renameObject\0hierarchyMenu\0loadTableItem\0"
    "QTableWidgetItem*\0objectSelected\0"
    "QTreeWidgetItem*\0loadObject\0viewPortChanged\0"
    "runButtonClicked\0loadScene\0updateProject\0"
    "updateOpenFolder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Editor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       3,    1,   77,    2, 0x08 /* Private */,
       4,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       6,    1,   86,    2, 0x08 /* Private */,
       8,    2,   89,    2, 0x08 /* Private */,
      10,    1,   94,    2, 0x08 /* Private */,
      11,    1,   97,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    2,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    2,    2,

       0        // eod
};

void Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Editor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setSceneViewFocus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->deleteObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->renameObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->hierarchyMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->loadTableItem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->objectSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->loadObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->viewPortChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->runButtonClicked(); break;
        case 9: _t->loadScene(); break;
        case 10: _t->updateProject(); break;
        case 11: _t->updateOpenFolder((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Editor::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Editor.data,
    qt_meta_data_Editor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Editor.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
