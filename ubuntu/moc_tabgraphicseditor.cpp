/****************************************************************************
** Meta object code from reading C++ file 'tabgraphicseditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/tabs/tabgraphicseditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tabgraphicseditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TabGraphicsEditor_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TabGraphicsEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TabGraphicsEditor_t qt_meta_stringdata_TabGraphicsEditor = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TabGraphicsEditor"
QT_MOC_LITERAL(1, 18, 15), // "enterSavePixmap"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "isScreen"
QT_MOC_LITERAL(4, 44, 10), // "quitReader"
QT_MOC_LITERAL(5, 55, 11), // "savePicture"
QT_MOC_LITERAL(6, 67, 8), // "QPixmap*"
QT_MOC_LITERAL(7, 76, 4) // "pict"

    },
    "TabGraphicsEditor\0enterSavePixmap\0\0"
    "isScreen\0quitReader\0savePicture\0"
    "QPixmap*\0pict"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TabGraphicsEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       1,    0,   42,    2, 0x26 /* Public | MethodCloned */,
       4,    1,   43,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void TabGraphicsEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TabGraphicsEditor *_t = static_cast<TabGraphicsEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enterSavePixmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->enterSavePixmap(); break;
        case 2: _t->quitReader((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->quitReader(); break;
        case 4: _t->savePicture((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TabGraphicsEditor::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabGraphicsEditor::enterSavePixmap)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TabGraphicsEditor::*_t)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabGraphicsEditor::quitReader)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TabGraphicsEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TabGraphicsEditor.data,
      qt_meta_data_TabGraphicsEditor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TabGraphicsEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabGraphicsEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TabGraphicsEditor.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TabGraphicsEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void TabGraphicsEditor::enterSavePixmap(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void TabGraphicsEditor::quitReader(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
