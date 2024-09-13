/****************************************************************************
** Meta object code from reading C++ file 'directoryselect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../directoryselect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'directoryselect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DirectorySelect_t {
    QByteArrayData data[9];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DirectorySelect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DirectorySelect_t qt_meta_stringdata_DirectorySelect = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DirectorySelect"
QT_MOC_LITERAL(1, 16, 14), // "selectFilePath"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "setGrillePath"
QT_MOC_LITERAL(4, 46, 19), // "setDisplayFramePath"
QT_MOC_LITERAL(5, 66, 10), // "setDatPath"
QT_MOC_LITERAL(6, 77, 9), // "setOxPath"
QT_MOC_LITERAL(7, 87, 11), // "setHeadPath"
QT_MOC_LITERAL(8, 99, 13) // "setBackupPath"

    },
    "DirectorySelect\0selectFilePath\0\0"
    "setGrillePath\0setDisplayFramePath\0"
    "setDatPath\0setOxPath\0setHeadPath\0"
    "setBackupPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DirectorySelect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

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

void DirectorySelect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DirectorySelect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
//        case 0: _t->selectFilePath(); break;
        case 1: _t->setGrillePath(); break;
        case 2: _t->setDisplayFramePath(); break;
        case 3: _t->setDatPath(); break;
        case 4: _t->setOxPath(); break;
        case 5: _t->setHeadPath(); break;
        case 6: _t->setBackupPath(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DirectorySelect::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DirectorySelect.data,
    qt_meta_data_DirectorySelect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DirectorySelect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DirectorySelect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DirectorySelect.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DirectorySelect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
