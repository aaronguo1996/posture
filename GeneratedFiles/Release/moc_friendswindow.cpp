/****************************************************************************
** Meta object code from reading C++ file 'friendswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../friendswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'friendswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FriendsWindow_t {
    QByteArrayData data[10];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FriendsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FriendsWindow_t qt_meta_stringdata_FriendsWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FriendsWindow"
QT_MOC_LITERAL(1, 14, 9), // "toFriends"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "deleteFriend"
QT_MOC_LITERAL(4, 38, 16), // "QAbstractButton*"
QT_MOC_LITERAL(5, 55, 9), // "toProfile"
QT_MOC_LITERAL(6, 65, 10), // "toProfileB"
QT_MOC_LITERAL(7, 76, 8), // "prevPage"
QT_MOC_LITERAL(8, 85, 8), // "nextPage"
QT_MOC_LITERAL(9, 94, 7) // "message"

    },
    "FriendsWindow\0toFriends\0\0deleteFriend\0"
    "QAbstractButton*\0toProfile\0toProfileB\0"
    "prevPage\0nextPage\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FriendsWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   52,    2, 0x08 /* Private */,
       5,    0,   55,    2, 0x08 /* Private */,
       6,    0,   56,    2, 0x08 /* Private */,
       7,    0,   57,    2, 0x08 /* Private */,
       8,    0,   58,    2, 0x08 /* Private */,
       9,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FriendsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FriendsWindow *_t = static_cast<FriendsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toFriends((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->deleteFriend((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->toProfile(); break;
        case 3: _t->toProfileB(); break;
        case 4: _t->prevPage(); break;
        case 5: _t->nextPage(); break;
        case 6: _t->message(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FriendsWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FriendsWindow::toFriends)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FriendsWindow::staticMetaObject = {
    { &PostureWindow::staticMetaObject, qt_meta_stringdata_FriendsWindow.data,
      qt_meta_data_FriendsWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FriendsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FriendsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FriendsWindow.stringdata0))
        return static_cast<void*>(const_cast< FriendsWindow*>(this));
    return PostureWindow::qt_metacast(_clname);
}

int FriendsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PostureWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FriendsWindow::toFriends(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
