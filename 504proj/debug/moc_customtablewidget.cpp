/****************************************************************************
** Meta object code from reading C++ file 'customtablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../customtablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customtablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_customTableWidget_t {
    QByteArrayData data[17];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_customTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_customTableWidget_t qt_meta_stringdata_customTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "customTableWidget"
QT_MOC_LITERAL(1, 18, 14), // "addButton_slot"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "deleteButton_slot"
QT_MOC_LITERAL(4, 52, 17), // "finishButton_slot"
QT_MOC_LITERAL(5, 70, 15), // "editButton_slot"
QT_MOC_LITERAL(6, 86, 17), // "searchButton_slot"
QT_MOC_LITERAL(7, 104, 17), // "cellDoubleClicked"
QT_MOC_LITERAL(8, 122, 3), // "row"
QT_MOC_LITERAL(9, 126, 6), // "column"
QT_MOC_LITERAL(10, 133, 10), // "importData"
QT_MOC_LITERAL(11, 144, 10), // "exportData"
QT_MOC_LITERAL(12, 155, 13), // "sendInfo_slot"
QT_MOC_LITERAL(13, 169, 4), // "port"
QT_MOC_LITERAL(14, 174, 4), // "logo"
QT_MOC_LITERAL(15, 179, 12), // "QHostAddress"
QT_MOC_LITERAL(16, 192, 4) // "addr"

    },
    "customTableWidget\0addButton_slot\0\0"
    "deleteButton_slot\0finishButton_slot\0"
    "editButton_slot\0searchButton_slot\0"
    "cellDoubleClicked\0row\0column\0importData\0"
    "exportData\0sendInfo_slot\0port\0logo\0"
    "QHostAddress\0addr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_customTableWidget[] = {

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
       7,    2,   64,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    3,   71,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UChar, 0x80000000 | 15,   13,   14,   16,

       0        // eod
};

void customTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<customTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addButton_slot(); break;
        case 1: _t->deleteButton_slot(); break;
        case 2: _t->finishButton_slot(); break;
        case 3: _t->editButton_slot(); break;
        case 4: _t->searchButton_slot(); break;
        case 5: _t->cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->importData(); break;
        case 7: _t->exportData(); break;
        case 8: _t->sendInfo_slot((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2])),(*reinterpret_cast< QHostAddress(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject customTableWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_customTableWidget.data,
    qt_meta_data_customTableWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *customTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *customTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_customTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int customTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
