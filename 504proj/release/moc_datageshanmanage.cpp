/****************************************************************************
** Meta object code from reading C++ file 'datageshanmanage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datageshanmanage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datageshanmanage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataGeshanManage_t {
    QByteArrayData data[14];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataGeshanManage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataGeshanManage_t qt_meta_stringdata_DataGeshanManage = {
    {
QT_MOC_LITERAL(0, 0, 16), // "DataGeshanManage"
QT_MOC_LITERAL(1, 17, 14), // "addButton_slot"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 17), // "deleteButton_slot"
QT_MOC_LITERAL(4, 51, 17), // "finishButton_slot"
QT_MOC_LITERAL(5, 69, 15), // "editButton_slot"
QT_MOC_LITERAL(6, 85, 17), // "searchButton_slot"
QT_MOC_LITERAL(7, 103, 13), // "download_slot"
QT_MOC_LITERAL(8, 117, 17), // "cellDoubleClicked"
QT_MOC_LITERAL(9, 135, 3), // "row"
QT_MOC_LITERAL(10, 139, 6), // "column"
QT_MOC_LITERAL(11, 146, 16), // "advanceCheckSlot"
QT_MOC_LITERAL(12, 163, 22), // "getAdvanceResultString"
QT_MOC_LITERAL(13, 186, 12) // "resultString"

    },
    "DataGeshanManage\0addButton_slot\0\0"
    "deleteButton_slot\0finishButton_slot\0"
    "editButton_slot\0searchButton_slot\0"
    "download_slot\0cellDoubleClicked\0row\0"
    "column\0advanceCheckSlot\0getAdvanceResultString\0"
    "resultString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataGeshanManage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    2,   65,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void DataGeshanManage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataGeshanManage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addButton_slot(); break;
        case 1: _t->deleteButton_slot(); break;
        case 2: _t->finishButton_slot(); break;
        case 3: _t->editButton_slot(); break;
        case 4: _t->searchButton_slot(); break;
        case 5: _t->download_slot(); break;
        case 6: _t->cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->advanceCheckSlot(); break;
        case 8: _t->getAdvanceResultString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataGeshanManage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DataGeshanManage.data,
    qt_meta_data_DataGeshanManage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataGeshanManage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataGeshanManage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataGeshanManage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DataGeshanManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
