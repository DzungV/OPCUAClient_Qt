/****************************************************************************
** Meta object code from reading C++ file 'QCodeEditor.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../newclient/OPCUAClient_Qt-master/include/KGL/Widgets/QCodeEditor.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCodeEditor.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_kgl__QCodeEditor_t {
    QByteArrayData data[13];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kgl__QCodeEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kgl__QCodeEditor_t qt_meta_stringdata_kgl__QCodeEditor = {
    {
QT_MOC_LITERAL(0, 0, 16), // "kgl::QCodeEditor"
QT_MOC_LITERAL(1, 17, 11), // "lineChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "QTextBlock"
QT_MOC_LITERAL(4, 41, 5), // "block"
QT_MOC_LITERAL(5, 47, 16), // "updateLineColumn"
QT_MOC_LITERAL(6, 64, 9), // "lineCount"
QT_MOC_LITERAL(7, 74, 16), // "scrollLineColumn"
QT_MOC_LITERAL(8, 91, 4), // "view"
QT_MOC_LITERAL(9, 96, 6), // "scroll"
QT_MOC_LITERAL(10, 103, 12), // "completeWord"
QT_MOC_LITERAL(11, 116, 4), // "word"
QT_MOC_LITERAL(12, 121, 11) // "textChanged"

    },
    "kgl::QCodeEditor\0lineChanged\0\0QTextBlock\0"
    "block\0updateLineColumn\0lineCount\0"
    "scrollLineColumn\0view\0scroll\0completeWord\0"
    "word\0textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kgl__QCodeEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   42,    2, 0x08 /* Private */,
       7,    2,   45,    2, 0x08 /* Private */,
      10,    1,   50,    2, 0x08 /* Private */,
      12,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

void kgl::QCodeEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCodeEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lineChanged((*reinterpret_cast< QTextBlock(*)>(_a[1]))); break;
        case 1: _t->updateLineColumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->scrollLineColumn((*reinterpret_cast< QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->completeWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->textChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCodeEditor::*)(QTextBlock );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCodeEditor::lineChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject kgl::QCodeEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<QPlainTextEdit::staticMetaObject>(),
    qt_meta_stringdata_kgl__QCodeEditor.data,
    qt_meta_data_kgl__QCodeEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *kgl::QCodeEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kgl::QCodeEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_kgl__QCodeEditor.stringdata0))
        return static_cast<void*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int kgl::QCodeEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void kgl::QCodeEditor::lineChanged(QTextBlock _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
