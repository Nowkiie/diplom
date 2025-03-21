/****************************************************************************
** Meta object code from reading C++ file 'sectorselectionmapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/sectorselectionmapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sectorselectionmapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry_t {
    QByteArrayData data[1];
    char stringdata0[37];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry_t qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry = {
    {
QT_MOC_LITERAL(0, 0, 36) // "qmapcontrol::SectorSelectionG..."

    },
    "qmapcontrol::SectorSelectionGeometry"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__SectorSelectionGeometry[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void qmapcontrol::SectorSelectionGeometry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::SectorSelectionGeometry::staticMetaObject = { {
    &qmapcontrol::StaticGeometry::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry.data,
    qt_meta_data_qmapcontrol__SectorSelectionGeometry,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::SectorSelectionGeometry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::SectorSelectionGeometry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__SectorSelectionGeometry.stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::StaticGeometry::qt_metacast(_clname);
}

int qmapcontrol::SectorSelectionGeometry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = qmapcontrol::StaticGeometry::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention_t {
    QByteArrayData data[11];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention_t qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 40), // "qmapcontrol::SectorSelectionM..."
QT_MOC_LITERAL(1, 41, 5), // "start"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 4), // "stop"
QT_MOC_LITERAL(4, 53, 13), // "MapExtention*"
QT_MOC_LITERAL(5, 67, 15), // "mouseMoveEvent_"
QT_MOC_LITERAL(6, 83, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 96, 4), // "evnt"
QT_MOC_LITERAL(8, 101, 10), // "coordinate"
QT_MOC_LITERAL(9, 112, 16), // "mousePressEvent_"
QT_MOC_LITERAL(10, 129, 18) // "mouseReleaseEvent_"

    },
    "qmapcontrol::SectorSelectionMapExtention\0"
    "start\0\0stop\0MapExtention*\0mouseMoveEvent_\0"
    "QMouseEvent*\0evnt\0coordinate\0"
    "mousePressEvent_\0mouseReleaseEvent_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__SectorSelectionMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    2,   43,    2, 0x08 /* Private */,
       9,    2,   48,    2, 0x08 /* Private */,
      10,    2,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPointF,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPointF,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPointF,    7,    8,

       0        // eod
};

void qmapcontrol::SectorSelectionMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SectorSelectionMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        case 2: _t->mouseMoveEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 3: _t->mousePressEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 4: _t->mouseReleaseEvent_((*reinterpret_cast< QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
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

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::SectorSelectionMapExtention::staticMetaObject = { {
    &SelectionMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention.data,
    qt_meta_data_qmapcontrol__SectorSelectionMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::SectorSelectionMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::SectorSelectionMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__SectorSelectionMapExtention.stringdata0))
        return static_cast<void*>(this);
    return SelectionMapExtention::qt_metacast(_clname);
}

int qmapcontrol::SectorSelectionMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SelectionMapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
