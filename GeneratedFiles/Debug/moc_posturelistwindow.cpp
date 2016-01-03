/****************************************************************************
** Meta object code from reading C++ file 'posturelistwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../posturelistwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'posturelistwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PostureListWindow_t {
    QByteArrayData data[11];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PostureListWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PostureListWindow_t qt_meta_stringdata_PostureListWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PostureListWindow"
QT_MOC_LITERAL(1, 18, 4), // "prev"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "next"
QT_MOC_LITERAL(4, 29, 7), // "display"
QT_MOC_LITERAL(5, 37, 10), // "ModelVideo"
QT_MOC_LITERAL(6, 48, 9), // "deletePos"
QT_MOC_LITERAL(7, 58, 9), // "toDisplay"
QT_MOC_LITERAL(8, 68, 9), // "toProfile"
QT_MOC_LITERAL(9, 78, 6), // "toPrev"
QT_MOC_LITERAL(10, 85, 6) // "toNext"

    },
    "PostureListWindow\0prev\0\0next\0display\0"
    "ModelVideo\0deletePos\0toDisplay\0toProfile\0"
    "toPrev\0toNext"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PostureListWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PostureListWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PostureListWindow *_t = static_cast<PostureListWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->prev((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->next((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->display((*reinterpret_cast< const ModelVideo(*)>(_a[1]))); break;
        case 3: _t->deletePos(); break;
        case 4: _t->toDisplay(); break;
        case 5: _t->toProfile(); break;
        case 6: _t->toPrev(); break;
        case 7: _t->toNext(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PostureListWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureListWindow::prev)) {
                *result = 0;
            }
        }
        {
            typedef void (PostureListWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureListWindow::next)) {
                *result = 1;
            }
        }
        {
            typedef void (PostureListWindow::*_t)(const ModelVideo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PostureListWindow::display)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject PostureListWindow::staticMetaObject = {
    { &PostureWindow::staticMetaObject, qt_meta_stringdata_PostureListWindow.data,
      qt_meta_data_PostureListWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PostureListWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PostureListWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PostureListWindow.stringdata0))
        return static_cast<void*>(const_cast< PostureListWindow*>(this));
    return PostureWindow::qt_metacast(_clname);
}

int PostureListWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PostureWindow::qt_metacall(_c, _id, _a);
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
void PostureListWindow::prev(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PostureListWindow::next(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PostureListWindow::display(const ModelVideo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
