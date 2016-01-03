/****************************************************************************
** Meta object code from reading C++ file 'uploadmodewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uploadmodewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uploadmodewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UploadModeWindow_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UploadModeWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UploadModeWindow_t qt_meta_stringdata_UploadModeWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "UploadModeWindow"
QT_MOC_LITERAL(1, 17, 8), // "toUpload"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "checkStoryValue"
QT_MOC_LITERAL(4, 43, 14), // "checkCardValue"
QT_MOC_LITERAL(5, 58, 6), // "record"
QT_MOC_LITERAL(6, 65, 7), // "prevPic"
QT_MOC_LITERAL(7, 73, 7) // "nextPic"

    },
    "UploadModeWindow\0toUpload\0\0checkStoryValue\0"
    "checkCardValue\0record\0prevPic\0nextPic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UploadModeWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   47,    2, 0x09 /* Protected */,
       4,    1,   50,    2, 0x09 /* Protected */,
       5,    0,   53,    2, 0x09 /* Protected */,
       6,    0,   54,    2, 0x09 /* Protected */,
       7,    0,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UploadModeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UploadModeWindow *_t = static_cast<UploadModeWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toUpload((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->checkStoryValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->checkCardValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->record(); break;
        case 4: _t->prevPic(); break;
        case 5: _t->nextPic(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UploadModeWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UploadModeWindow::toUpload)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject UploadModeWindow::staticMetaObject = {
    { &PostureWindow::staticMetaObject, qt_meta_stringdata_UploadModeWindow.data,
      qt_meta_data_UploadModeWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UploadModeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UploadModeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UploadModeWindow.stringdata0))
        return static_cast<void*>(const_cast< UploadModeWindow*>(this));
    return PostureWindow::qt_metacast(_clname);
}

int UploadModeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PostureWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void UploadModeWindow::toUpload(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
