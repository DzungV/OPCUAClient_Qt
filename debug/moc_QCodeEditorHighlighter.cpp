/****************************************************************************
** Meta object code from reading C++ file 'QCodeEditorHighlighter.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../newclient/OPCUAClient_Qt-master/include/KGL/Widgets/QCodeEditorHighlighter.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCodeEditorHighlighter.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_kgl__QCodeEditorHighlighter_t {
    QByteArrayData data[14];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_kgl__QCodeEditorHighlighter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_kgl__QCodeEditorHighlighter_t qt_meta_stringdata_kgl__QCodeEditorHighlighter = {
    {
QT_MOC_LITERAL(0, 0, 27), // "kgl::QCodeEditorHighlighter"
QT_MOC_LITERAL(1, 28, 7), // "onMatch"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "QSyntaxRule"
QT_MOC_LITERAL(4, 49, 4), // "rule"
QT_MOC_LITERAL(5, 54, 8), // "sequence"
QT_MOC_LITERAL(6, 63, 10), // "QTextBlock"
QT_MOC_LITERAL(7, 74, 5), // "block"
QT_MOC_LITERAL(8, 80, 11), // "onHighlight"
QT_MOC_LITERAL(9, 92, 23), // "QCodeEditorHighlighter*"
QT_MOC_LITERAL(10, 116, 11), // "highlighter"
QT_MOC_LITERAL(11, 128, 8), // "onRemove"
QT_MOC_LITERAL(12, 137, 21), // "QCodeEditorBlockData*"
QT_MOC_LITERAL(13, 159, 4) // "data"

    },
    "kgl::QCodeEditorHighlighter\0onMatch\0"
    "\0QSyntaxRule\0rule\0sequence\0QTextBlock\0"
    "block\0onHighlight\0QCodeEditorHighlighter*\0"
    "highlighter\0onRemove\0QCodeEditorBlockData*\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_kgl__QCodeEditorHighlighter[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       8,    1,   36,    2, 0x06 /* Public */,
      11,    1,   39,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void kgl::QCodeEditorHighlighter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCodeEditorHighlighter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMatch((*reinterpret_cast< const QSyntaxRule(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QTextBlock(*)>(_a[3]))); break;
        case 1: _t->onHighlight((*reinterpret_cast< QCodeEditorHighlighter*(*)>(_a[1]))); break;
        case 2: _t->onRemove((*reinterpret_cast< QCodeEditorBlockData*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCodeEditorHighlighter* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCodeEditorHighlighter::*)(const QSyntaxRule & , QString , QTextBlock );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCodeEditorHighlighter::onMatch)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCodeEditorHighlighter::*)(QCodeEditorHighlighter * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCodeEditorHighlighter::onHighlight)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCodeEditorHighlighter::*)(QCodeEditorBlockData * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCodeEditorHighlighter::onRemove)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject kgl::QCodeEditorHighlighter::staticMetaObject = { {
    QMetaObject::SuperData::link<QSyntaxHighlighter::staticMetaObject>(),
    qt_meta_stringdata_kgl__QCodeEditorHighlighter.data,
    qt_meta_data_kgl__QCodeEditorHighlighter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *kgl::QCodeEditorHighlighter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *kgl::QCodeEditorHighlighter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_kgl__QCodeEditorHighlighter.stringdata0))
        return static_cast<void*>(this);
    return QSyntaxHighlighter::qt_metacast(_clname);
}

int kgl::QCodeEditorHighlighter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSyntaxHighlighter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void kgl::QCodeEditorHighlighter::onMatch(const QSyntaxRule & _t1, QString _t2, QTextBlock _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void kgl::QCodeEditorHighlighter::onHighlight(QCodeEditorHighlighter * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void kgl::QCodeEditorHighlighter::onRemove(QCodeEditorBlockData * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
