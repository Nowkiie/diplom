/****************************************************************************
** Meta object code from reading C++ file 'createplacemapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/createplacemapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createplacemapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention_t {
    QByteArrayData data[16];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention_t qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 36), // "qmapcontrol::CreatePlaceMapEx..."
QT_MOC_LITERAL(1, 37, 5), // "start"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 4), // "stop"
QT_MOC_LITERAL(4, 49, 13), // "MapExtention*"
QT_MOC_LITERAL(5, 63, 6), // "sender"
QT_MOC_LITERAL(6, 70, 8), // "setColor"
QT_MOC_LITERAL(7, 79, 5), // "color"
QT_MOC_LITERAL(8, 85, 9), // "setRadius"
QT_MOC_LITERAL(9, 95, 6), // "radius"
QT_MOC_LITERAL(10, 102, 15), // "mouseMoveEvent_"
QT_MOC_LITERAL(11, 118, 12), // "QMouseEvent*"
QT_MOC_LITERAL(12, 131, 1), // "e"
QT_MOC_LITERAL(13, 133, 10), // "coordinate"
QT_MOC_LITERAL(14, 144, 16), // "mousePressEvent_"
QT_MOC_LITERAL(15, 161, 18) // "mouseReleaseEvent_"

    },
    "qmapcontrol::CreatePlaceMapExtention\0"
    "start\0\0stop\0MapExtention*\0sender\0"
    "setColor\0color\0setRadius\0radius\0"
    "mouseMoveEvent_\0QMouseEvent*\0e\0"
    "coordinate\0mousePressEvent_\0"
    "mouseReleaseEvent_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__CreatePlaceMapExtention[] = {

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
       3,    1,   50,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
      10,    2,   59,    2, 0x08 /* Private */,
      14,    2,   64,    2, 0x08 /* Private */,
      15,    2,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QPointF,   12,   13,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QPointF,   12,   13,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QPointF,   12,   13,

       0        // eod
};

void qmapcontrol::CreatePlaceMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreatePlaceMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 3: _t->setRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->mouseMoveEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 5: _t->mousePressEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 6: _t->mouseReleaseEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MapExtention* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::CreatePlaceMapExtention::staticMetaObject = { {
    &qmapcontrol::GeometryCreatorMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention.data,
    qt_meta_data_qmapcontrol__CreatePlaceMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::CreatePlaceMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::CreatePlaceMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__CreatePlaceMapExtention.stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::GeometryCreatorMapExtention::qt_metacast(_clname);
}

int qmapcontrol::CreatePlaceMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = qmapcontrol::GeometryCreatorMapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
