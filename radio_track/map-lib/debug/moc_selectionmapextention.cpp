/****************************************************************************
** Meta object code from reading C++ file 'selectionmapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/selectionmapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectionmapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__SelectionMapExtention_t {
    QByteArrayData data[11];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__SelectionMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__SelectionMapExtention_t qt_meta_stringdata_qmapcontrol__SelectionMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 34), // "qmapcontrol::SelectionMapExte..."
QT_MOC_LITERAL(1, 35, 8), // "selected"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 16), // "QList<Geometry*>"
QT_MOC_LITERAL(4, 62, 10), // "geometries"
QT_MOC_LITERAL(5, 73, 41), // "SelectionMapExtention::Select..."
QT_MOC_LITERAL(6, 115, 9), // "modifiers"
QT_MOC_LITERAL(7, 125, 5), // "start"
QT_MOC_LITERAL(8, 131, 4), // "stop"
QT_MOC_LITERAL(9, 136, 13), // "MapExtention*"
QT_MOC_LITERAL(10, 150, 6) // "sender"

    },
    "qmapcontrol::SelectionMapExtention\0"
    "selected\0\0QList<Geometry*>\0geometries\0"
    "SelectionMapExtention::SelectionModifiers\0"
    "modifiers\0start\0stop\0MapExtention*\0"
    "sender"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__SelectionMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   34,    2, 0x0a /* Public */,
       8,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void qmapcontrol::SelectionMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectionMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selected((*reinterpret_cast< QList<Geometry*>(*)>(_a[1])),(*reinterpret_cast< SelectionMapExtention::SelectionModifiers(*)>(_a[2]))); break;
        case 1: _t->start(); break;
        case 2: _t->stop((*reinterpret_cast< MapExtention*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<Geometry*> >(); break;
            }
            break;
        case 2:
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
            using _t = void (SelectionMapExtention::*)(QList<Geometry*> , SelectionMapExtention::SelectionModifiers );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectionMapExtention::selected)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::SelectionMapExtention::staticMetaObject = { {
    &qmapcontrol::CheckableMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__SelectionMapExtention.data,
    qt_meta_data_qmapcontrol__SelectionMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::SelectionMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::SelectionMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__SelectionMapExtention.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "qmapcontrol::GeometryProcessor"))
        return static_cast< qmapcontrol::GeometryProcessor*>(this);
    return qmapcontrol::CheckableMapExtention::qt_metacast(_clname);
}

int qmapcontrol::SelectionMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void qmapcontrol::SelectionMapExtention::selected(QList<Geometry*> _t1, SelectionMapExtention::SelectionModifiers _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
