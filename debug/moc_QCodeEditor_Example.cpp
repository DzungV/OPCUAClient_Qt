/****************************************************************************
** Meta object code from reading C++ file 'QCodeEditor_Example.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../QCodeEditor_Example.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCodeEditor_Example.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_kgl__QCodeEditor_Example_t {
    QByteArrayData data[11];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kgl__QCodeEditor_Example_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kgl__QCodeEditor_Example_t qt_meta_stringdata_kgl__QCodeEditor_Example = {
    {
QT_MOC_LITERAL(0, 0, 24), // "kgl::QCodeEditor_Example"
QT_MOC_LITERAL(1, 25, 8), // "addMacro"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "QSyntaxRule"
QT_MOC_LITERAL(4, 47, 4), // "rule"
QT_MOC_LITERAL(5, 52, 3), // "seq"
QT_MOC_LITERAL(6, 56, 10), // "QTextBlock"
QT_MOC_LITERAL(7, 67, 5), // "block"
QT_MOC_LITERAL(8, 73, 11), // "removeMacro"
QT_MOC_LITERAL(9, 85, 21), // "QCodeEditorBlockData*"
QT_MOC_LITERAL(10, 107, 4) // "data"

    },
    "kgl::QCodeEditor_Example\0addMacro\0\0"
    "QSyntaxRule\0rule\0seq\0QTextBlock\0block\0"
    "removeMacro\0QCodeEditorBlockData*\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kgl__QCodeEditor_Example[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x08 /* Private */,
       8,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void kgl::QCodeEditor_Example::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCodeEditor_Example *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addMacro((*reinterpret_cast< const QSyntaxRule(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QTextBlock(*)>(_a[3]))); break;
        case 1: _t->removeMacro((*reinterpret_cast< QCodeEditorBlockData*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject kgl::QCodeEditor_Example::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_kgl__QCodeEditor_Example.data,
    qt_meta_data_kgl__QCodeEditor_Example,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *kgl::QCodeEditor_Example::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kgl::QCodeEditor_Example::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_kgl__QCodeEditor_Example.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int kgl::QCodeEditor_Example::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
