/****************************************************************************
** Meta object code from reading C++ file 'mapnetworkfactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/mapnetworkfactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'mapnetworkfactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__MapNetworkFactory_t
{
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                          \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                   \
        len,                                                                   \
        qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__MapNetworkFactory_t, \
                          stringdata0)                                         \
                 + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__MapNetworkFactory_t
    qt_meta_stringdata_qmapcontrol__MapNetworkFactory = {
        {
            QT_MOC_LITERAL(0, 0, 30),   // "qmapcontrol::MapNetworkFactory"
            QT_MOC_LITERAL(1, 31, 12),  // "mapConnected"
            QT_MOC_LITERAL(2, 44, 0),   // ""
            QT_MOC_LITERAL(3, 45, 7),   // "mapName"
            QT_MOC_LITERAL(4, 53, 9),   // "mapNameUi"
            QT_MOC_LITERAL(5, 63, 11)   // "layersCount"

        },
        "qmapcontrol::MapNetworkFactory\0"
        "mapConnected\0\0mapName\0mapNameUi\0"
        "layersCount"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__MapNetworkFactory[] = {

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
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, 3,
    4, 5,

    0  // eod
};

void qmapcontrol::MapNetworkFactory::qt_static_metacall(QObject* _o,
                                                        QMetaObject::Call _c,
                                                        int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<MapNetworkFactory*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->mapConnected((*reinterpret_cast<QString(*)>(_a[1])),
                                 (*reinterpret_cast<QString(*)>(_a[2])),
                                 (*reinterpret_cast<int(*)>(_a[3])));
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (MapNetworkFactory::*)(QString, QString, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkFactory::mapConnected))
            {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::MapNetworkFactory::staticMetaObject = {
        {&QObject::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__MapNetworkFactory.data,
         qt_meta_data_qmapcontrol__MapNetworkFactory, qt_static_metacall,
         nullptr, nullptr}};

const QMetaObject* qmapcontrol::MapNetworkFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::MapNetworkFactory::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_qmapcontrol__MapNetworkFactory.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::MapNetworkFactory::qt_metacall(QMetaObject::Call _c, int _id,
                                                void** _a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void qmapcontrol::MapNetworkFactory::mapConnected(QString _t1, QString _t2,
                                                  int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
