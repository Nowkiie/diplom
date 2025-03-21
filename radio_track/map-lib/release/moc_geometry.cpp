/****************************************************************************
** Meta object code from reading C++ file 'geometry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/geometries/geometry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'geometry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__Geometry_t
{
    QByteArrayData data[18];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                      \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(               \
        len, qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__Geometry_t, \
                               stringdata0)                                \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__Geometry_t
    qt_meta_stringdata_qmapcontrol__Geometry = {
        {
            QT_MOC_LITERAL(0, 0, 21),     // "qmapcontrol::Geometry"
            QT_MOC_LITERAL(1, 22, 10),    // "mouseEnter"
            QT_MOC_LITERAL(2, 33, 0),     // ""
            QT_MOC_LITERAL(3, 34, 9),     // "Geometry*"
            QT_MOC_LITERAL(4, 44, 6),     // "sender"
            QT_MOC_LITERAL(5, 51, 12),    // "QMouseEvent*"
            QT_MOC_LITERAL(6, 64, 1),     // "e"
            QT_MOC_LITERAL(7, 66, 9),     // "mouseOver"
            QT_MOC_LITERAL(8, 76, 10),    // "mouseLeave"
            QT_MOC_LITERAL(9, 87, 10),    // "mouseClick"
            QT_MOC_LITERAL(10, 98, 16),   // "mouseDoubleClick"
            QT_MOC_LITERAL(11, 115, 21),  // "updateRequestGeometry"
            QT_MOC_LITERAL(12, 137, 4),   // "geom"
            QT_MOC_LITERAL(13, 142, 17),  // "updateRequestRect"
            QT_MOC_LITERAL(14, 160, 4),   // "rect"
            QT_MOC_LITERAL(15, 165, 15),  // "positionChanged"
            QT_MOC_LITERAL(16, 181, 10),  // "setVisible"
            QT_MOC_LITERAL(17, 192, 7)    // "visible"

        },
        "qmapcontrol::Geometry\0mouseEnter\0\0"
        "Geometry*\0sender\0QMouseEvent*\0e\0"
        "mouseOver\0mouseLeave\0mouseClick\0"
        "mouseDoubleClick\0updateRequestGeometry\0"
        "geom\0updateRequestRect\0rect\0positionChanged\0"
        "setVisible\0visible"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__Geometry[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    9, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    8,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 2, 59, 2, 0x06 /* Public */, 7, 2, 64, 2, 0x06 /* Public */, 8, 2, 69, 2,
    0x06 /* Public */, 9, 2, 74, 2, 0x06 /* Public */, 10, 2, 79, 2,
    0x06 /* Public */, 11, 1, 84, 2, 0x06 /* Public */, 13, 1, 87, 2,
    0x06 /* Public */, 15, 1, 90, 2, 0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    16, 1, 93, 2, 0x0a /* Public */,

    // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 4, 6, QMetaType::Void,
    0x80000000 | 3, 0x80000000 | 5, 4, 6, QMetaType::Void, 0x80000000 | 3,
    0x80000000 | 5, 4, 6, QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 4, 6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 4, 6, QMetaType::Void,
    0x80000000 | 3, 12, QMetaType::Void, QMetaType::QRectF, 14, QMetaType::Void,
    0x80000000 | 3, 12,

    // slots: parameters
    QMetaType::Void, QMetaType::Bool, 17,

    0  // eod
};

void qmapcontrol::Geometry::qt_static_metacall(QObject* _o,
                                               QMetaObject::Call _c, int _id,
                                               void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<Geometry*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->mouseEnter((*reinterpret_cast<Geometry*(*)>(_a[1])),
                               (*reinterpret_cast<QMouseEvent*(*)>(_a[2])));
                break;
            case 1:
                _t->mouseOver((*reinterpret_cast<Geometry*(*)>(_a[1])),
                              (*reinterpret_cast<QMouseEvent*(*)>(_a[2])));
                break;
            case 2:
                _t->mouseLeave((*reinterpret_cast<Geometry*(*)>(_a[1])),
                               (*reinterpret_cast<QMouseEvent*(*)>(_a[2])));
                break;
            case 3:
                _t->mouseClick((*reinterpret_cast<Geometry*(*)>(_a[1])),
                               (*reinterpret_cast<QMouseEvent*(*)>(_a[2])));
                break;
            case 4:
                _t->mouseDoubleClick(
                    (*reinterpret_cast<Geometry*(*)>(_a[1])),
                    (*reinterpret_cast<QMouseEvent*(*)>(_a[2])));
                break;
            case 5:
                _t->updateRequestGeometry(
                    (*reinterpret_cast<Geometry*(*)>(_a[1])));
                break;
            case 6:
                _t->updateRequestRect((*reinterpret_cast<QRectF(*)>(_a[1])));
                break;
            case 7:
                _t->positionChanged((*reinterpret_cast<Geometry*(*)>(_a[1])));
                break;
            case 8:
                _t->setVisible((*reinterpret_cast<bool(*)>(_a[1])));
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        switch (_id)
        {
            default:
                *reinterpret_cast<int*>(_a[0]) = -1;
                break;
            case 0:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 1:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 2:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 3:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 4:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 5:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
            case 7:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<Geometry*>();
                        break;
                }
                break;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (Geometry::*)(Geometry*, QMouseEvent*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::mouseEnter))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*, QMouseEvent*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::mouseOver))
            {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*, QMouseEvent*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::mouseLeave))
            {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*, QMouseEvent*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::mouseClick))
            {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*, QMouseEvent*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::mouseDoubleClick))
            {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::updateRequestGeometry))
            {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(QRectF);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::updateRequestRect))
            {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Geometry::*)(Geometry*);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Geometry::positionChanged))
            {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::Geometry::staticMetaObject = {
    {&QObject::staticMetaObject, qt_meta_stringdata_qmapcontrol__Geometry.data,
     qt_meta_data_qmapcontrol__Geometry, qt_static_metacall, nullptr, nullptr}};

const QMetaObject* qmapcontrol::Geometry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::Geometry::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__Geometry.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::Geometry::qt_metacall(QMetaObject::Call _c, int _id, void** _a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::Geometry::mouseEnter(Geometry* _t1, QMouseEvent* _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::Geometry::mouseOver(Geometry* _t1, QMouseEvent* _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qmapcontrol::Geometry::mouseLeave(Geometry* _t1, QMouseEvent* _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qmapcontrol::Geometry::mouseClick(Geometry* _t1, QMouseEvent* _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void qmapcontrol::Geometry::mouseDoubleClick(Geometry* _t1, QMouseEvent* _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void qmapcontrol::Geometry::updateRequestGeometry(Geometry* _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void qmapcontrol::Geometry::updateRequestRect(QRectF _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void qmapcontrol::Geometry::positionChanged(Geometry* _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
