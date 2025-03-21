/****************************************************************************
** Meta object code from reading C++ file 'mapnetworkclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/mapnetworkclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'mapnetworkclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__MapNetworkClient_t
{
    QByteArrayData data[17];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                         \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                  \
        len,                                                                  \
        qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__MapNetworkClient_t, \
                          stringdata0)                                        \
                 + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__MapNetworkClient_t
    qt_meta_stringdata_qmapcontrol__MapNetworkClient = {
        {
            QT_MOC_LITERAL(0, 0, 29),     // "qmapcontrol::MapNetworkClient"
            QT_MOC_LITERAL(1, 30, 12),    // "mapConnected"
            QT_MOC_LITERAL(2, 43, 0),     // ""
            QT_MOC_LITERAL(3, 44, 7),     // "mapName"
            QT_MOC_LITERAL(4, 52, 9),     // "mapNameUi"
            QT_MOC_LITERAL(5, 62, 11),    // "layersCount"
            QT_MOC_LITERAL(6, 74, 12),    // "tileRecieved"
            QT_MOC_LITERAL(7, 87, 1),     // "x"
            QT_MOC_LITERAL(8, 89, 1),     // "y"
            QT_MOC_LITERAL(9, 91, 1),     // "z"
            QT_MOC_LITERAL(10, 93, 5),    // "layer"
            QT_MOC_LITERAL(11, 99, 5),    // "image"
            QT_MOC_LITERAL(12, 105, 9),   // "tileEmpty"
            QT_MOC_LITERAL(13, 115, 20),  // "mapConnectedInternal"
            QT_MOC_LITERAL(14, 136, 20),  // "tileRecievedInternal"
            QT_MOC_LITERAL(15, 157, 17),  // "tileEmptyInternal"
            QT_MOC_LITERAL(16, 175, 8)    // "getImage"

        },
        "qmapcontrol::MapNetworkClient\0"
        "mapConnected\0\0mapName\0mapNameUi\0"
        "layersCount\0tileRecieved\0x\0y\0z\0layer\0"
        "image\0tileEmpty\0mapConnectedInternal\0"
        "tileRecievedInternal\0tileEmptyInternal\0"
        "getImage"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__MapNetworkClient[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    7, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    6,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 3, 49, 2, 0x06 /* Public */, 6, 6, 56, 2, 0x06 /* Public */, 12, 5, 69,
    2, 0x06 /* Public */, 13, 3, 80, 2, 0x06 /* Public */, 14, 6, 87, 2,
    0x06 /* Public */, 15, 5, 100, 2, 0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    16, 5, 111, 2, 0x0a /* Public */,

    // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, 3,
    4, 5, QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, QMetaType::Int, QMetaType::QPixmap, 3, 7, 8, 9, 10, 11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, QMetaType::Int, 3, 7, 8, 9, 10, QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::Int, 3, 4, 5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, QMetaType::Int, QMetaType::QPixmap, 3, 7, 8, 9, 10, 11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, QMetaType::Int, 3, 7, 8, 9, 10,

    // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, QMetaType::Int, 3, 7, 8, 9, 10,

    0  // eod
};

void qmapcontrol::MapNetworkClient::qt_static_metacall(QObject* _o,
                                                       QMetaObject::Call _c,
                                                       int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<MapNetworkClient*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->mapConnected((*reinterpret_cast<QString(*)>(_a[1])),
                                 (*reinterpret_cast<QString(*)>(_a[2])),
                                 (*reinterpret_cast<int(*)>(_a[3])));
                break;
            case 1:
                _t->tileRecieved((*reinterpret_cast<QString(*)>(_a[1])),
                                 (*reinterpret_cast<int(*)>(_a[2])),
                                 (*reinterpret_cast<int(*)>(_a[3])),
                                 (*reinterpret_cast<int(*)>(_a[4])),
                                 (*reinterpret_cast<int(*)>(_a[5])),
                                 (*reinterpret_cast<QPixmap(*)>(_a[6])));
                break;
            case 2:
                _t->tileEmpty((*reinterpret_cast<QString(*)>(_a[1])),
                              (*reinterpret_cast<int(*)>(_a[2])),
                              (*reinterpret_cast<int(*)>(_a[3])),
                              (*reinterpret_cast<int(*)>(_a[4])),
                              (*reinterpret_cast<int(*)>(_a[5])));
                break;
            case 3:
                _t->mapConnectedInternal((*reinterpret_cast<QString(*)>(_a[1])),
                                         (*reinterpret_cast<QString(*)>(_a[2])),
                                         (*reinterpret_cast<int(*)>(_a[3])));
                break;
            case 4:
                _t->tileRecievedInternal(
                    (*reinterpret_cast<QString(*)>(_a[1])),
                    (*reinterpret_cast<int(*)>(_a[2])),
                    (*reinterpret_cast<int(*)>(_a[3])),
                    (*reinterpret_cast<int(*)>(_a[4])),
                    (*reinterpret_cast<int(*)>(_a[5])),
                    (*reinterpret_cast<QPixmap(*)>(_a[6])));
                break;
            case 5:
                _t->tileEmptyInternal((*reinterpret_cast<QString(*)>(_a[1])),
                                      (*reinterpret_cast<int(*)>(_a[2])),
                                      (*reinterpret_cast<int(*)>(_a[3])),
                                      (*reinterpret_cast<int(*)>(_a[4])),
                                      (*reinterpret_cast<int(*)>(_a[5])));
                break;
            case 6:
                _t->getImage((*reinterpret_cast<QString(*)>(_a[1])),
                             (*reinterpret_cast<int(*)>(_a[2])),
                             (*reinterpret_cast<int(*)>(_a[3])),
                             (*reinterpret_cast<int(*)>(_a[4])),
                             (*reinterpret_cast<int(*)>(_a[5])));
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (MapNetworkClient::*)(QString, QString, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::mapConnected))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MapNetworkClient::*)(QString, int, int, int, int,
                                                  QPixmap);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::tileRecieved))
            {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MapNetworkClient::*)(QString, int, int, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::tileEmpty))
            {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MapNetworkClient::*)(QString, QString, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::mapConnectedInternal))
            {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MapNetworkClient::*)(QString, int, int, int, int,
                                                  QPixmap);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::tileRecievedInternal))
            {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MapNetworkClient::*)(QString, int, int, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapNetworkClient::tileEmptyInternal))
            {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::MapNetworkClient::staticMetaObject = {
        {&QObject::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__MapNetworkClient.data,
         qt_meta_data_qmapcontrol__MapNetworkClient, qt_static_metacall,
         nullptr, nullptr}};

const QMetaObject* qmapcontrol::MapNetworkClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::MapNetworkClient::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_qmapcontrol__MapNetworkClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::MapNetworkClient::qt_metacall(QMetaObject::Call _c, int _id,
                                               void** _a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::MapNetworkClient::mapConnected(QString _t1, QString _t2,
                                                 int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::MapNetworkClient::tileRecieved(QString _t1, int _t2, int _t3,
                                                 int _t4, int _t5, QPixmap _t6)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t4)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t5)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t6))};
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void qmapcontrol::MapNetworkClient::tileEmpty(QString _t1, int _t2, int _t3,
                                              int _t4, int _t5)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t4)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t5))};
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void qmapcontrol::MapNetworkClient::mapConnectedInternal(QString _t1,
                                                         QString _t2, int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void qmapcontrol::MapNetworkClient::tileRecievedInternal(QString _t1, int _t2,
                                                         int _t3, int _t4,
                                                         int _t5, QPixmap _t6)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t4)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t5)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t6))};
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void qmapcontrol::MapNetworkClient::tileEmptyInternal(QString _t1, int _t2,
                                                      int _t3, int _t4, int _t5)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t4)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t5))};
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
