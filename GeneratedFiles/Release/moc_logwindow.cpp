/****************************************************************************
** Meta object code from reading C++ file 'logwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../logwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LogWindow_t {
    QByteArrayData data[9];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogWindow_t qt_meta_stringdata_LogWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "LogWindow"
QT_MOC_LITERAL(1, 10, 10), // "logSuccess"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 10), // "regSuccess"
QT_MOC_LITERAL(4, 33, 4), // "wait"
QT_MOC_LITERAL(5, 38, 6), // "change"
QT_MOC_LITERAL(6, 45, 6), // "commit"
QT_MOC_LITERAL(7, 52, 5), // "toLog"
QT_MOC_LITERAL(8, 58, 5) // "toReg"

    },
    "LogWindow\0logSuccess\0\0regSuccess\0wait\0"
    "change\0commit\0toLog\0toReg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LogWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LogWindow *_t = static_cast<LogWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logSuccess(); break;
        case 1: _t->regSuccess(); break;
        case 2: _t->wait(); break;
        case 3: _t->change(); break;
        case 4: _t->commit(); break;
        case 5: _t->toLog(); break;
        case 6: _t->toReg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LogWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LogWindow::logSuccess)) {
                *result = 0;
            }
        }
        {
            typedef void (LogWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LogWindow::regSuccess)) {
                *result = 1;
            }
        }
        {
            typedef void (LogWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LogWindow::wait)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LogWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LogWindow.data,
      qt_meta_data_LogWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LogWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LogWindow.stringdata0))
        return static_cast<void*>(const_cast< LogWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int LogWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void LogWindow::logSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void LogWindow::regSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void LogWindow::wait()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
