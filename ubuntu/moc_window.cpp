/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/tabs/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Wind_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Wind_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Wind_t qt_meta_stringdata_Wind = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Wind"
QT_MOC_LITERAL(1, 5, 14), // "enterFullScrin"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 17), // "enterPartOfScreen"
QT_MOC_LITERAL(4, 39, 13), // "enterSettings"
QT_MOC_LITERAL(5, 53, 12), // "enterHistory"
QT_MOC_LITERAL(6, 66, 9), // "enterOpen"
QT_MOC_LITERAL(7, 76, 9), // "enterCopy"
QT_MOC_LITERAL(8, 86, 7), // "hideWin"
QT_MOC_LITERAL(9, 94, 7), // "showWin"
QT_MOC_LITERAL(10, 102, 7) // "destroy"

    },
    "Wind\0enterFullScrin\0\0enterPartOfScreen\0"
    "enterSettings\0enterHistory\0enterOpen\0"
    "enterCopy\0hideWin\0showWin\0destroy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Wind[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Wind::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Wind *_t = static_cast<Wind *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enterFullScrin(); break;
        case 1: _t->enterPartOfScreen(); break;
        case 2: _t->enterSettings(); break;
        case 3: _t->enterHistory(); break;
        case 4: _t->enterOpen(); break;
        case 5: _t->enterCopy(); break;
        case 6: _t->hideWin(); break;
        case 7: _t->showWin(); break;
        case 8: _t->destroy(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterFullScrin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterPartOfScreen)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterSettings)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterHistory)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterOpen)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Wind::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Wind::enterCopy)) {
                *result = 5;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Wind::staticMetaObject = {
    { &TabBase::staticMetaObject, qt_meta_stringdata_Wind.data,
      qt_meta_data_Wind,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Wind::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Wind::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Wind.stringdata0))
        return static_cast<void*>(this);
    return TabBase::qt_metacast(_clname);
}

int Wind::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TabBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Wind::enterFullScrin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Wind::enterPartOfScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Wind::enterSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Wind::enterHistory()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Wind::enterOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Wind::enterCopy()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
