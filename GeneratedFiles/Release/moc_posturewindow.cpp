/****************************************************************************
** Meta object code from reading C++ file 'posturewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../posturewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'posturewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PostureWindow_t {
    QByteArrayData data[10];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PostureWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PostureWindow_t qt_meta_stringdata_PostureWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PostureWindow"
QT_MOC_LITERAL(1, 14, 13), // "toProfileMode"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "toHome"
QT_MOC_LITERAL(4, 36, 8), // "toSearch"
QT_MOC_LITERAL(5, 45, 8), // "toUpload"
QT_MOC_LITERAL(6, 54, 6), // "logout"
QT_MOC_LITERAL(7, 61, 7), // "refresh"
QT_MOC_LITERAL(8, 69, 10), // "checkValue"
QT_MOC_LITERAL(9, 80, 9) // "toProfile"

    },
    "PostureWindow\0toProfileMode\0\0toHome\0"
    "toSearch\0toUpload\0logout\0refresh\0"
    "checkValue\0toProfile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PostureWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    0,   57,    2, 0x06 /* Public */,
       4,    0,   58,    2, 0x06 /* Public */,
       5,    0,   59,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,
       7,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   62,    2, 0x09 /* Protected */,
       9,    0,   65,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void PostureWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PostureWindow *_t = static_cast<PostureWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toProfileMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->toHome(); break;
        case 2: _t->toSearch(); break;
        case 3: _t->toUpload(); break;
        case 4: _t->logout(); break;
        case 5: _t->refresh(); break;
        case 6: _t->checkValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->toProfile(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PostureWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::toProfileMode)) {
                *result = 0;
            }
        }
        {
            typedef void (PostureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::toHome)) {
                *result = 1;
            }
        }
        {
            typedef void (PostureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::toSearch)) {
                *result = 2;
            }
        }
        {
            typedef void (PostureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::toUpload)) {
                *result = 3;
            }
        }
        {
            typedef void (PostureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::logout)) {
                *result = 4;
            }
        }
        {
            typedef void (PostureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureWindow::refresh)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject PostureWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PostureWindow.data,
      qt_meta_data_PostureWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PostureWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PostureWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PostureWindow.stringdata0))
        return static_cast<void*>(const_cast< PostureWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int PostureWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PostureWindow::toProfileMode(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PostureWindow::toHome()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void PostureWindow::toSearch()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PostureWindow::toUpload()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PostureWindow::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void PostureWindow::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
