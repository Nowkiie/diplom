/****************************************************************************
** Meta object code from reading C++ file 'selectormapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/selectormapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectormapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__SelectorMapExtention_t {
    QByteArrayData data[7];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__SelectorMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__SelectorMapExtention_t qt_meta_stringdata_qmapcontrol__SelectorMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 33), // "qmapcontrol::SelectorMapExten..."
QT_MOC_LITERAL(1, 34, 15), // "mouseMoveEvent_"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 64, 4), // "evnt"
QT_MOC_LITERAL(5, 69, 10), // "coordinate"
QT_MOC_LITERAL(6, 80, 16) // "mousePressEvent_"

    },
    "qmapcontrol::SelectorMapExtention\0"
    "mouseMoveEvent_\0\0QMouseEvent*\0evnt\0"
    "coordinate\0mousePressEvent_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__SelectorMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x08 /* Private */,
       6,    2,   29,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,

       0        // eod
};

void qmapcontrol::SelectorMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectorMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseMoveEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 1: _t->mousePressEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::SelectorMapExtention::staticMetaObject = { {
    &MapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__SelectorMapExtention.data,
    qt_meta_data_qmapcontrol__SelectorMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::SelectorMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::SelectorMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__SelectorMapExtention.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "GeometryProcessor"))
        return static_cast< GeometryProcessor*>(this);
    return MapExtention::qt_metacast(_clname);
}

int qmapcontrol::SelectorMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
