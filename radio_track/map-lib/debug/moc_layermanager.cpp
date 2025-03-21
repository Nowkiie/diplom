/****************************************************************************
** Meta object code from reading C++ file 'layermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/layermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'layermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__LayerManager_t {
    QByteArrayData data[13];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__LayerManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__LayerManager_t qt_meta_stringdata_qmapcontrol__LayerManager = {
    {
QT_MOC_LITERAL(0, 0, 25), // "qmapcontrol::LayerManager"
QT_MOC_LITERAL(1, 26, 17), // "updateRequestRect"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 4), // "rect"
QT_MOC_LITERAL(4, 50, 13), // "updateRequest"
QT_MOC_LITERAL(5, 64, 6), // "resize"
QT_MOC_LITERAL(6, 71, 7), // "newSize"
QT_MOC_LITERAL(7, 79, 20), // "updateRequestNewTile"
QT_MOC_LITERAL(8, 100, 1), // "x"
QT_MOC_LITERAL(9, 102, 1), // "y"
QT_MOC_LITERAL(10, 104, 1), // "z"
QT_MOC_LITERAL(11, 106, 16), // "updateRequestNew"
QT_MOC_LITERAL(12, 123, 15) // "loadingFinished"

    },
    "qmapcontrol::LayerManager\0updateRequestRect\0"
    "\0rect\0updateRequest\0resize\0newSize\0"
    "updateRequestNewTile\0x\0y\0z\0updateRequestNew\0"
    "loadingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__LayerManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       4,    0,   47,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       7,    3,   51,    2, 0x0a /* Public */,
      11,    0,   58,    2, 0x0a /* Public */,
      12,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QRectF,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void qmapcontrol::LayerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LayerManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateRequestRect((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 1: _t->updateRequest(); break;
        case 2: _t->resize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 3: _t->updateRequestNewTile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->updateRequestNew(); break;
        case 5: _t->loadingFinished(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::LayerManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__LayerManager.data,
    qt_meta_data_qmapcontrol__LayerManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::LayerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::LayerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__LayerManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::LayerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
