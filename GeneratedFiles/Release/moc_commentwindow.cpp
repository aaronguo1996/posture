/****************************************************************************
** Meta object code from reading C++ file 'commentwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../commentwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commentwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CommentWindow_t {
    QByteArrayData data[12];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CommentWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CommentWindow_t qt_meta_stringdata_CommentWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CommentWindow"
QT_MOC_LITERAL(1, 14, 9), // "toDisplay"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "ModelVideo"
QT_MOC_LITERAL(4, 36, 13), // "toProfileMode"
QT_MOC_LITERAL(5, 50, 11), // "updateModel"
QT_MOC_LITERAL(6, 62, 9), // "toComment"
QT_MOC_LITERAL(7, 72, 7), // "comment"
QT_MOC_LITERAL(8, 80, 8), // "toReturn"
QT_MOC_LITERAL(9, 89, 9), // "toProfile"
QT_MOC_LITERAL(10, 99, 8), // "prevPage"
QT_MOC_LITERAL(11, 108, 8) // "nextPage"

    },
    "CommentWindow\0toDisplay\0\0ModelVideo\0"
    "toProfileMode\0updateModel\0toComment\0"
    "comment\0toReturn\0toProfile\0prevPage\0"
    "nextPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommentWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   76,    2, 0x08 /* Private */,
       6,    0,   77,    2, 0x08 /* Private */,
       8,    0,   78,    2, 0x08 /* Private */,
       9,    0,   79,    2, 0x08 /* Private */,
      10,    0,   80,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CommentWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CommentWindow *_t = static_cast<CommentWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toDisplay((*reinterpret_cast< const ModelVideo(*)>(_a[1]))); break;
        case 1: _t->toProfileMode((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateModel((*reinterpret_cast< const ModelVideo(*)>(_a[1]))); break;
        case 3: _t->toComment((*reinterpret_cast< const ModelVideo(*)>(_a[1]))); break;
        case 4: _t->comment(); break;
        case 5: _t->toComment(); break;
        case 6: _t->toReturn(); break;
        case 7: _t->toProfile(); break;
        case 8: _t->prevPage(); break;
        case 9: _t->nextPage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CommentWindow::*_t)(const ModelVideo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CommentWindow::toDisplay)) {
                *result = 0;
            }
        }
        {
            typedef void (CommentWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CommentWindow::toProfileMode)) {
                *result = 1;
            }
        }
        {
            typedef void (CommentWindow::*_t)(const ModelVideo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CommentWindow::updateModel)) {
                *result = 2;
            }
        }
        {
            typedef void (CommentWindow::*_t)(const ModelVideo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CommentWindow::toComment)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject CommentWindow::staticMetaObject = {
    { &PostureWindow::staticMetaObject, qt_meta_stringdata_CommentWindow.data,
      qt_meta_data_CommentWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CommentWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommentWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CommentWindow.stringdata0))
        return static_cast<void*>(const_cast< CommentWindow*>(this));
    return PostureWindow::qt_metacast(_clname);
}

int CommentWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PostureWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CommentWindow::toDisplay(const ModelVideo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CommentWindow::toProfileMode(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CommentWindow::updateModel(const ModelVideo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CommentWindow::toComment(const ModelVideo & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
