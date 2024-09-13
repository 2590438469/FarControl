/****************************************************************************
** Meta object code from reading C++ file 'sendfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sendfile/sendfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sendfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sendfile_t {
    QByteArrayData data[19];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sendfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sendfile_t qt_meta_stringdata_sendfile = {
    {
QT_MOC_LITERAL(0, 0, 8), // "sendfile"
QT_MOC_LITERAL(1, 9, 7), // "sendPro"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 7), // "nowsize"
QT_MOC_LITERAL(4, 26, 7), // "allsize"
QT_MOC_LITERAL(5, 34, 12), // "sendFileData"
QT_MOC_LITERAL(6, 47, 5), // "array"
QT_MOC_LITERAL(7, 53, 12), // "abortConnect"
QT_MOC_LITERAL(8, 66, 12), // "sendProgress"
QT_MOC_LITERAL(9, 79, 8), // "sendFile"
QT_MOC_LITERAL(10, 88, 19), // "sendfile::FILE_TYPE"
QT_MOC_LITERAL(11, 108, 4), // "type"
QT_MOC_LITERAL(12, 113, 9), // "stationIp"
QT_MOC_LITERAL(13, 123, 8), // "filename"
QT_MOC_LITERAL(14, 132, 8), // "progress"
QT_MOC_LITERAL(15, 141, 12), // "parentString"
QT_MOC_LITERAL(16, 154, 13), // "sendAbortFile"
QT_MOC_LITERAL(17, 168, 14), // "sendDianziFile"
QT_MOC_LITERAL(18, 183, 10) // "deleteSlot"

    },
    "sendfile\0sendPro\0\0nowsize\0allsize\0"
    "sendFileData\0array\0abortConnect\0"
    "sendProgress\0sendFile\0sendfile::FILE_TYPE\0"
    "type\0stationIp\0filename\0progress\0"
    "parentString\0sendAbortFile\0sendDianziFile\0"
    "deleteSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sendfile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    0,   62,    2, 0x06 /* Public */,
       8,    2,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    5,   68,    2, 0x0a /* Public */,
      16,    4,   79,    2, 0x0a /* Public */,
      17,    5,   88,    2, 0x0a /* Public */,
      18,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong,    3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString, QMetaType::QString, QMetaType::ULongLong, QMetaType::QString,   11,   12,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString, QMetaType::QString, QMetaType::ULongLong,   11,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString, QMetaType::QString, QMetaType::ULongLong, QMetaType::QString,   11,   12,   13,   14,   15,
    QMetaType::Void,

       0        // eod
};

void sendfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sendfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendPro((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 1: _t->sendFileData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->abortConnect(); break;
        case 3: _t->sendProgress((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 4: _t->sendFile((*reinterpret_cast< sendfile::FILE_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 5: _t->sendAbortFile((*reinterpret_cast< sendfile::FILE_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4]))); break;
        case 6: _t->sendDianziFile((*reinterpret_cast< sendfile::FILE_TYPE(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 7: _t->deleteSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< sendfile::FILE_TYPE >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< sendfile::FILE_TYPE >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< sendfile::FILE_TYPE >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sendfile::*)(quint64 , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sendfile::sendPro)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (sendfile::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sendfile::sendFileData)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (sendfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sendfile::abortConnect)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (sendfile::*)(quint64 , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sendfile::sendProgress)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sendfile::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_sendfile.data,
    qt_meta_data_sendfile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sendfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sendfile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sendfile.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sendfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void sendfile::sendPro(quint64 _t1, quint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sendfile::sendFileData(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void sendfile::abortConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void sendfile::sendProgress(quint64 _t1, quint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
