/****************************************************************************
** Meta object code from reading C++ file 'layer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/layer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__Layer_t {
    QByteArrayData data[14];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__Layer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__Layer_t qt_meta_stringdata_qmapcontrol__Layer = {
    {
QT_MOC_LITERAL(0, 0, 18), // "qmapcontrol::Layer"
QT_MOC_LITERAL(1, 19, 17), // "updateRequestRect"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "rect"
QT_MOC_LITERAL(4, 43, 13), // "updateRequest"
QT_MOC_LITERAL(5, 57, 17), // "imageReceivedTile"
QT_MOC_LITERAL(6, 75, 1), // "x"
QT_MOC_LITERAL(7, 77, 1), // "y"
QT_MOC_LITERAL(8, 79, 1), // "z"
QT_MOC_LITERAL(9, 81, 15), // "loadingFinished"
QT_MOC_LITERAL(10, 97, 13), // "imageReceived"
QT_MOC_LITERAL(11, 111, 10), // "setVisible"
QT_MOC_LITERAL(12, 122, 7), // "visible"
QT_MOC_LITERAL(13, 130, 16) // "checkDoubleClick"

    },
    "qmapcontrol::Layer\0updateRequestRect\0"
    "\0rect\0updateRequest\0imageReceivedTile\0"
    "x\0y\0z\0loadingFinished\0imageReceived\0"
    "setVisible\0visible\0checkDoubleClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__Layer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    0,   52,    2, 0x06 /* Public */,
       5,    3,   53,    2, 0x06 /* Public */,
       9,    0,   60,    2, 0x06 /* Public */,
      10,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   62,    2, 0x0a /* Public */,
      13,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QRectF,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

void qmapcontrol::Layer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Layer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateRequestRect((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->updateRequest(); break;
        case 2: _t->imageReceivedTile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->loadingFinished(); break;
        case 4: _t->imageReceived(); break;
        case 5: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->checkDoubleClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Layer::*)(QRectF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Layer::updateRequestRect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Layer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Layer::updateRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Layer::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Layer::imageReceivedTile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Layer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Layer::loadingFinished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Layer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Layer::imageReceived)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::Layer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__Layer.data,
    qt_meta_data_qmapcontrol__Layer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::Layer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::Layer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__Layer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::Layer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void qmapcontrol::Layer::updateRequestRect(QRectF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::Layer::updateRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void qmapcontrol::Layer::imageReceivedTile(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qmapcontrol::Layer::loadingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void qmapcontrol::Layer::imageReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
