/****************************************************************************
** Meta object code from reading C++ file 'welcomewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../welcomewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcomewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WelcomeWindow_t {
    QByteArrayData data[7];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WelcomeWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WelcomeWindow_t qt_meta_stringdata_WelcomeWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WelcomeWindow"
QT_MOC_LITERAL(1, 14, 7), // "display"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "ModelVideo"
QT_MOC_LITERAL(4, 34, 4), // "prev"
QT_MOC_LITERAL(5, 39, 4), // "next"
QT_MOC_LITERAL(6, 44, 7) // "refresh"

    },
    "WelcomeWindow\0display\0\0ModelVideo\0"
    "prev\0next\0refresh"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WelcomeWindow[] = {

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
       4,    0,   42,    2, 0x06 /* Public */,
       5,    0,   43,    2, 0x06 /* Public */,
       6,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       1,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void WelcomeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WelcomeWindow *_t = static_cast<WelcomeWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->display((*reinterpret_cast< const ModelVideo(*)>(_a[1]))); break;
        case 1: _t->prev(); break;
        case 2: _t->next(); break;
        case 3: _t->refresh(); break;
        case 4: _t->display(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WelcomeWindow::*_t)(const ModelVideo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeWindow::display)) {
                *result = 0;
            }
        }
        {
            typedef void (WelcomeWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeWindow::prev)) {
                *result = 1;
            }
        }
        {
            typedef void (WelcomeWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeWindow::next)) {
                *result = 2;
            }
        }
        {
            typedef void (WelcomeWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeWindow::refresh)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject WelcomeWindow::staticMetaObject = {
    { &PostureWindow::staticMetaObject, qt_meta_stringdata_WelcomeWindow.data,
      qt_meta_data_WelcomeWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WelcomeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WelcomeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WelcomeWindow.stringdata0))
        return static_cast<void*>(const_cast< WelcomeWindow*>(this));
    return PostureWindow::qt_metacast(_clname);
}

int WelcomeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PostureWindow::qt_metacall(_c, _id, _a);
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
void WelcomeWindow::display(const ModelVideo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WelcomeWindow::prev()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void WelcomeWindow::next()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void WelcomeWindow::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
