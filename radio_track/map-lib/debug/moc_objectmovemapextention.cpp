/****************************************************************************
** Meta object code from reading C++ file 'objectmovemapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/objectmovemapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectmovemapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention_t {
    QByteArrayData data[15];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention_t qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 35), // "qmapcontrol::ObjectMoveMapExt..."
QT_MOC_LITERAL(1, 36, 11), // "objectMoved"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 9), // "Geometry*"
QT_MOC_LITERAL(4, 59, 6), // "object"
QT_MOC_LITERAL(5, 66, 14), // "objectSelected"
QT_MOC_LITERAL(6, 81, 5), // "start"
QT_MOC_LITERAL(7, 87, 4), // "stop"
QT_MOC_LITERAL(8, 92, 13), // "MapExtention*"
QT_MOC_LITERAL(9, 106, 15), // "mouseMoveEvent_"
QT_MOC_LITERAL(10, 122, 12), // "QMouseEvent*"
QT_MOC_LITERAL(11, 135, 4), // "evnt"
QT_MOC_LITERAL(12, 140, 10), // "coordinate"
QT_MOC_LITERAL(13, 151, 16), // "mousePressEvent_"
QT_MOC_LITERAL(14, 168, 18) // "mouseReleaseEvent_"

    },
    "qmapcontrol::ObjectMoveMapExtention\0"
    "objectMoved\0\0Geometry*\0object\0"
    "objectSelected\0start\0stop\0MapExtention*\0"
    "mouseMoveEvent_\0QMouseEvent*\0evnt\0"
    "coordinate\0mousePressEvent_\0"
    "mouseReleaseEvent_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__ObjectMoveMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    2,   59,    2, 0x08 /* Private */,
      13,    2,   64,    2, 0x08 /* Private */,
      14,    2,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QPointF,   11,   12,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QPointF,   11,   12,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QPointF,   11,   12,

       0        // eod
};

void qmapcontrol::ObjectMoveMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ObjectMoveMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->objectMoved((*reinterpret_cast< Geometry*(*)>(_a[1]))); break;
        case 1: _t->objectSelected((*reinterpret_cast< Geometry*(*)>(_a[1]))); break;
        case 2: _t->start(); break;
        case 3: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        case 4: _t->mouseMoveEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 5: _t->mousePressEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 6: _t->mouseReleaseEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Geometry* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Geometry* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MapExtention* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ObjectMoveMapExtention::*)(Geometry * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectMoveMapExtention::objectMoved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ObjectMoveMapExtention::*)(Geometry * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ObjectMoveMapExtention::objectSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::ObjectMoveMapExtention::staticMetaObject = { {
    &CheckableMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention.data,
    qt_meta_data_qmapcontrol__ObjectMoveMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::ObjectMoveMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::ObjectMoveMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__ObjectMoveMapExtention.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "GeometryProcessor"))
        return static_cast< GeometryProcessor*>(this);
    return CheckableMapExtention::qt_metacast(_clname);
}

int qmapcontrol::ObjectMoveMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CheckableMapExtention::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void qmapcontrol::ObjectMoveMapExtention::objectMoved(Geometry * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::ObjectMoveMapExtention::objectSelected(Geometry * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
