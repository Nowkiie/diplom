/****************************************************************************
** Meta object code from reading C++ file 'citylabelsmapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/citylabelsmapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'citylabelsmapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention_t {
    QByteArrayData data[8];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention_t qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 35), // "qmapcontrol::CityLabelsMapExt..."
QT_MOC_LITERAL(1, 36, 10), // "setChecked"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 7), // "checked"
QT_MOC_LITERAL(4, 56, 5), // "start"
QT_MOC_LITERAL(5, 62, 4), // "stop"
QT_MOC_LITERAL(6, 67, 13), // "MapExtention*"
QT_MOC_LITERAL(7, 81, 6) // "sender"

    },
    "qmapcontrol::CityLabelsMapExtention\0"
    "setChecked\0\0checked\0start\0stop\0"
    "MapExtention*\0sender"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__CityLabelsMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    0,   32,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void qmapcontrol::CityLabelsMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CityLabelsMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->start(); break;
        case 2: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MapExtention* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::CityLabelsMapExtention::staticMetaObject = { {
    &qmapcontrol::CheckableMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention.data,
    qt_meta_data_qmapcontrol__CityLabelsMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::CityLabelsMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::CityLabelsMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__CityLabelsMapExtention.stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::CheckableMapExtention::qt_metacast(_clname);
}

int qmapcontrol::CityLabelsMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = qmapcontrol::CheckableMapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
