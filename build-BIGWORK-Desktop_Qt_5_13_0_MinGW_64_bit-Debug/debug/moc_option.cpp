/****************************************************************************
** Meta object code from reading C++ file 'option.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../BIGWORK/option.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'option.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Option_t {
    QByteArrayData data[16];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Option_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Option_t qt_meta_stringdata_Option = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Option"
QT_MOC_LITERAL(1, 7, 8), // "sendSize"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9), // "sendInput"
QT_MOC_LITERAL(4, 27, 18), // "std::pair<int,int>"
QT_MOC_LITERAL(5, 46, 10), // "sendOutput"
QT_MOC_LITERAL(6, 57, 12), // "sendGenerate"
QT_MOC_LITERAL(7, 70, 11), // "clearVector"
QT_MOC_LITERAL(8, 82, 14), // "clearVectorOut"
QT_MOC_LITERAL(9, 97, 5), // "shows"
QT_MOC_LITERAL(10, 103, 8), // "pushInIn"
QT_MOC_LITERAL(11, 112, 9), // "pushInOut"
QT_MOC_LITERAL(12, 122, 11), // "generateDot"
QT_MOC_LITERAL(13, 134, 12), // "updateButton"
QT_MOC_LITERAL(14, 147, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(15, 171, 23) // "on_pushButton_5_clicked"

    },
    "Option\0sendSize\0\0sendInput\0"
    "std::pair<int,int>\0sendOutput\0"
    "sendGenerate\0clearVector\0clearVectorOut\0"
    "shows\0pushInIn\0pushInOut\0generateDot\0"
    "updateButton\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Option[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       3,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       6,    1,   90,    2, 0x06 /* Public */,
       7,    0,   93,    2, 0x06 /* Public */,
       8,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   95,    2, 0x08 /* Private */,
      10,    0,   96,    2, 0x08 /* Private */,
      11,    0,   97,    2, 0x08 /* Private */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Option::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Option *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sendInput((*reinterpret_cast< std::pair<int,int>(*)>(_a[1]))); break;
        case 2: _t->sendOutput((*reinterpret_cast< std::pair<int,int>(*)>(_a[1]))); break;
        case 3: _t->sendGenerate((*reinterpret_cast< std::pair<int,int>(*)>(_a[1]))); break;
        case 4: _t->clearVector(); break;
        case 5: _t->clearVectorOut(); break;
        case 6: _t->shows(); break;
        case 7: _t->pushInIn(); break;
        case 8: _t->pushInOut(); break;
        case 9: _t->generateDot(); break;
        case 10: _t->updateButton(); break;
        case 11: _t->on_pushButton_4_clicked(); break;
        case 12: _t->on_pushButton_5_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Option::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::sendSize)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Option::*)(std::pair<int,int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::sendInput)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Option::*)(std::pair<int,int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::sendOutput)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Option::*)(std::pair<int,int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::sendGenerate)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Option::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::clearVector)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Option::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Option::clearVectorOut)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Option::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_Option.data,
    qt_meta_data_Option,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Option::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Option::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Option.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Option::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Option::sendSize(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Option::sendInput(std::pair<int,int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Option::sendOutput(std::pair<int,int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Option::sendGenerate(std::pair<int,int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Option::clearVector()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Option::clearVectorOut()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
