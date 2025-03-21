/****************************************************************************
** Meta object code from reading C++ file 'layer_req.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../request_tile/layer_req.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'layer_req.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__Layer_req_t
{
    QByteArrayData data[6];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                       \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                \
        len, qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__Layer_req_t, \
                               stringdata0)                                 \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__Layer_req_t
    qt_meta_stringdata_qmapcontrol__Layer_req = {
        {
            QT_MOC_LITERAL(0, 0, 22),  // "qmapcontrol::Layer_req"
            QT_MOC_LITERAL(1, 23, 9),  // "tile_load"
            QT_MOC_LITERAL(2, 33, 0),  // ""
            QT_MOC_LITERAL(3, 34, 6),  // "pixmap"
            QT_MOC_LITERAL(4, 41, 1),  // "x"
            QT_MOC_LITERAL(5, 43, 1)   // "y"

        },
        "qmapcontrol::Layer_req\0tile_load\0\0"
        "pixmap\0x\0y"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__Layer_req[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    1, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    1,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 3, 19, 2, 0x06 /* Public */,

    // signals: parameters
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int, QMetaType::Int, 3, 4,
    5,

    0  // eod
};

void qmapcontrol::Layer_req::qt_static_metacall(QObject* _o,
                                                QMetaObject::Call _c, int _id,
                                                void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<Layer_req*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->tile_load((*reinterpret_cast<const QPixmap(*)>(_a[1])),
                              (*reinterpret_cast<int(*)>(_a[2])),
                              (*reinterpret_cast<int(*)>(_a[3])));
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (Layer_req::*)(const QPixmap, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&Layer_req::tile_load))
            {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::Layer_req::staticMetaObject =
    {{&Layer::staticMetaObject, qt_meta_stringdata_qmapcontrol__Layer_req.data,
      qt_meta_data_qmapcontrol__Layer_req, qt_static_metacall, nullptr,
      nullptr}};

const QMetaObject* qmapcontrol::Layer_req::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::Layer_req::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__Layer_req.stringdata0))
        return static_cast<void*>(this);
    return Layer::qt_metacast(_clname);
}

int qmapcontrol::Layer_req::qt_metacall(QMetaObject::Call _c, int _id,
                                        void** _a)
{
    _id = Layer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::Layer_req::tile_load(const QPixmap _t1, int _t2, int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
