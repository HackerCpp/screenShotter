/****************************************************************************
** Meta object code from reading C++ file 'tray.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/tabs/tray.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tray_t {
    QByteArrayData data[9];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tray_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tray_t qt_meta_stringdata_Tray = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tray"
QT_MOC_LITERAL(1, 5, 14), // "leftMouseClick"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 15), // "rightMouseClick"
QT_MOC_LITERAL(4, 37, 10), // "mouseclick"
QT_MOC_LITERAL(5, 48, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(6, 82, 4), // "reas"
QT_MOC_LITERAL(7, 87, 12), // "messageClick"
QT_MOC_LITERAL(8, 100, 7) // "addMenu"

    },
    "Tray\0leftMouseClick\0\0rightMouseClick\0"
    "mouseclick\0QSystemTrayIcon::ActivationReason\0"
    "reas\0messageClick\0addMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tray[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   41,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tray *_t = static_cast<Tray *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->leftMouseClick(); break;
        case 1: _t->rightMouseClick(); break;
        case 2: _t->mouseclick((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 3: _t->messageClick(); break;
        case 4: _t->addMenu(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Tray::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tray::leftMouseClick)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Tray::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Tray::rightMouseClick)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Tray::staticMetaObject = {
    { &QSystemTrayIcon::staticMetaObject, qt_meta_stringdata_Tray.data,
      qt_meta_data_Tray,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Tray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tray::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tray.stringdata0))
        return static_cast<void*>(this);
    return QSystemTrayIcon::qt_metacast(_clname);
}

int Tray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSystemTrayIcon::qt_metacall(_c, _id, _a);
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
void Tray::leftMouseClick()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Tray::rightMouseClick()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
