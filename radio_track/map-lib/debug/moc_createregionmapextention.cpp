/****************************************************************************
** Meta object code from reading C++ file 'createregionmapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/createregionmapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createregionmapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention_t {
    QByteArrayData data[17];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention_t qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 37), // "qmapcontrol::CreateRegionMapE..."
QT_MOC_LITERAL(1, 38, 5), // "start"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 4), // "stop"
QT_MOC_LITERAL(4, 50, 13), // "MapExtention*"
QT_MOC_LITERAL(5, 64, 6), // "sender"
QT_MOC_LITERAL(6, 71, 8), // "setColor"
QT_MOC_LITERAL(7, 80, 5), // "color"
QT_MOC_LITERAL(8, 86, 12), // "setFillStyle"
QT_MOC_LITERAL(9, 99, 14), // "Qt::BrushStyle"
QT_MOC_LITERAL(10, 114, 9), // "fillStyle"
QT_MOC_LITERAL(11, 124, 15), // "mouseMoveEvent_"
QT_MOC_LITERAL(12, 140, 12), // "QMouseEvent*"
QT_MOC_LITERAL(13, 153, 1), // "e"
QT_MOC_LITERAL(14, 155, 10), // "coordinate"
QT_MOC_LITERAL(15, 166, 16), // "mousePressEvent_"
QT_MOC_LITERAL(16, 183, 18) // "mouseReleaseEvent_"

    },
    "qmapcontrol::CreateRegionMapExtention\0"
    "start\0\0stop\0MapExtention*\0sender\0"
    "setColor\0color\0setFillStyle\0Qt::BrushStyle\0"
    "fillStyle\0mouseMoveEvent_\0QMouseEvent*\0"
    "e\0coordinate\0mousePressEvent_\0"
    "mouseReleaseEvent_"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__CreateRegionMapExtention[] = {

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
      11,    2,   59,    2, 0x08 /* Private */,
      15,    2,   64,    2, 0x08 /* Private */,
      16,    2,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QColor,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QPointF,   13,   14,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QPointF,   13,   14,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QPointF,   13,   14,

       0        // eod
};

void qmapcontrol::CreateRegionMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateRegionMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start(); break;
        case 1: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        case 2: _t->setColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 3: _t->setFillStyle((*reinterpret_cast< Qt::BrushStyle(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::CreateRegionMapExtention::staticMetaObject = { {
    &qmapcontrol::GeometryCreatorMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention.data,
    qt_meta_data_qmapcontrol__CreateRegionMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::CreateRegionMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::CreateRegionMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__CreateRegionMapExtention.stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::GeometryCreatorMapExtention::qt_metacast(_clname);
}

int qmapcontrol::CreateRegionMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
