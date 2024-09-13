/****************************************************************************
** Meta object code from reading C++ file 'missionreview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../missionreview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'missionreview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_missionreview_t {
    QByteArrayData data[22];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_missionreview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_missionreview_t qt_meta_stringdata_missionreview = {
    {
QT_MOC_LITERAL(0, 0, 13), // "missionreview"
QT_MOC_LITERAL(1, 14, 7), // "sendStr"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "sendNewStr"
QT_MOC_LITERAL(4, 34, 8), // "sendFile"
QT_MOC_LITERAL(5, 43, 8), // "filepath"
QT_MOC_LITERAL(6, 52, 4), // "node"
QT_MOC_LITERAL(7, 57, 3), // "ip1"
QT_MOC_LITERAL(8, 61, 3), // "ip2"
QT_MOC_LITERAL(9, 65, 6), // "getStr"
QT_MOC_LITERAL(10, 72, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(11, 96, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(12, 118, 25), // "on_pushButton_yes_clicked"
QT_MOC_LITERAL(13, 144, 24), // "on_pushButton_no_clicked"
QT_MOC_LITERAL(14, 169, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(15, 193, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(16, 217, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(17, 241, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(18, 265, 6), // "getPro"
QT_MOC_LITERAL(19, 272, 7), // "nowsize"
QT_MOC_LITERAL(20, 280, 7), // "allsize"
QT_MOC_LITERAL(21, 288, 10) // "finishSend"

    },
    "missionreview\0sendStr\0\0sendNewStr\0"
    "sendFile\0filepath\0node\0ip1\0ip2\0getStr\0"
    "on_pushButton_2_clicked\0on_pushButton_clicked\0"
    "on_pushButton_yes_clicked\0"
    "on_pushButton_no_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_6_clicked\0"
    "getPro\0nowsize\0allsize\0finishSend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_missionreview[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    3,   87,    2, 0x06 /* Public */,
       4,    4,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  103,    2, 0x08 /* Private */,
      10,    0,  106,    2, 0x08 /* Private */,
      11,    0,  107,    2, 0x08 /* Private */,
      12,    0,  108,    2, 0x08 /* Private */,
      13,    0,  109,    2, 0x08 /* Private */,
      14,    0,  110,    2, 0x08 /* Private */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    0,  112,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    2,  114,    2, 0x08 /* Private */,
      21,    0,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong,   19,   20,
    QMetaType::Void,

       0        // eod
};

void missionreview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<missionreview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendStr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendNewStr((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->sendFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->getStr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_2_clicked(); break;
        case 5: _t->on_pushButton_clicked(); break;
        case 6: _t->on_pushButton_yes_clicked(); break;
        case 7: _t->on_pushButton_no_clicked(); break;
        case 8: _t->on_pushButton_5_clicked(); break;
        case 9: _t->on_pushButton_4_clicked(); break;
        case 10: _t->on_pushButton_3_clicked(); break;
//        case 11: _t->on_pushButton_6_clicked(); break;
        case 12: _t->getPro((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2]))); break;
        case 13: _t->finishSend(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (missionreview::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&missionreview::sendStr)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (missionreview::*)(QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&missionreview::sendNewStr)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (missionreview::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&missionreview::sendFile)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject missionreview::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_missionreview.data,
    qt_meta_data_missionreview,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *missionreview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *missionreview::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_missionreview.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int missionreview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void missionreview::sendStr(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void missionreview::sendNewStr(QString _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void missionreview::sendFile(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
