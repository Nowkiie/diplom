/****************************************************************************
** Meta object code from reading C++ file 'geometryconnectormapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/geometryconnectormapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error \
        "The header file 'geometryconnectormapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator_t
{
    QByteArrayData data[3];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                                    \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                             \
        len,                                                                             \
        qptrdiff(                                                                        \
            offsetof(                                                                    \
                qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator_t, \
                stringdata0)                                                             \
            + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator_t
    qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator = {
        {
            QT_MOC_LITERAL(0, 0, 50),   // "qmapcontrol::GeometryConnecto..."
            QT_MOC_LITERAL(1, 51, 17),  // "geometriesUpdated"
            QT_MOC_LITERAL(2, 69, 0)    // ""

        },
        "qmapcontrol::GeometryConnectorCoordinateTranslator\0"
        "geometriesUpdated\0"};
#undef QT_MOC_LITERAL

static const uint
    qt_meta_data_qmapcontrol__GeometryConnectorCoordinateTranslator[] = {

        // content:
        8,      // revision
        0,      // classname
        0, 0,   // classinfo
        1, 14,  // methods
        0, 0,   // properties
        0, 0,   // enums/sets
        0, 0,   // constructors
        0,      // flags
        0,      // signalCount

        // slots: name, argc, parameters, tag, flags
        1, 0, 19, 2, 0x08 /* Private */,

        // slots: parameters
        QMetaType::Void,

        0  // eod
};

void qmapcontrol::GeometryConnectorCoordinateTranslator::qt_static_metacall(
    QObject* _o, QMetaObject::Call _c, int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<GeometryConnectorCoordinateTranslator*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->geometriesUpdated();
                break;
            default:;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::GeometryConnectorCoordinateTranslator::staticMetaObject = {
        {&QObject::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator
             .data,
         qt_meta_data_qmapcontrol__GeometryConnectorCoordinateTranslator,
         qt_static_metacall, nullptr, nullptr}};

const QMetaObject*
    qmapcontrol::GeometryConnectorCoordinateTranslator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::GeometryConnectorCoordinateTranslator::qt_metacast(
    const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(
            _clname,
            qt_meta_stringdata_qmapcontrol__GeometryConnectorCoordinateTranslator
                .stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "GeometryProcessor"))
        return static_cast<GeometryProcessor*>(this);
    if (!strcmp(_clname, "CoordinateTranslator"))
        return static_cast<CoordinateTranslator*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::GeometryConnectorCoordinateTranslator::qt_metacall(
    QMetaObject::Call _c, int _id, void** _a)
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
struct qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention_t
{
    QByteArrayData data[10];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                            \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                     \
        len,                                                                     \
        qptrdiff(                                                                \
            offsetof(                                                            \
                qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention_t, \
                stringdata0)                                                     \
            + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention_t
    qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention = {
        {
            QT_MOC_LITERAL(0, 0, 42),   // "qmapcontrol::GeometryConnecto..."
            QT_MOC_LITERAL(1, 43, 5),   // "start"
            QT_MOC_LITERAL(2, 49, 0),   // ""
            QT_MOC_LITERAL(3, 50, 4),   // "stop"
            QT_MOC_LITERAL(4, 55, 13),  // "MapExtention*"
            QT_MOC_LITERAL(5, 69, 6),   // "sender"
            QT_MOC_LITERAL(6, 76, 10),  // "setChecked"
            QT_MOC_LITERAL(7, 87, 7),   // "checked"
            QT_MOC_LITERAL(8, 95, 12),  // "zoomChanged_"
            QT_MOC_LITERAL(9, 108, 4)   // "zoom"

        },
        "qmapcontrol::GeometryConnectorMapExtention\0"
        "start\0\0stop\0MapExtention*\0sender\0"
        "setChecked\0checked\0zoomChanged_\0zoom"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__GeometryConnectorMapExtention[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    4, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    0,      // signalCount

    // slots: name, argc, parameters, tag, flags
    1, 0, 34, 2, 0x0a /* Public */, 3, 1, 35, 2, 0x0a /* Public */, 6, 1, 38, 2,
    0x0a /* Public */, 8, 1, 41, 2, 0x08 /* Private */,

    // slots: parameters
    QMetaType::Void, QMetaType::Void, 0x80000000 | 4, 5, QMetaType::Void,
    QMetaType::Bool, 7, QMetaType::Void, QMetaType::Int, 9,

    0  // eod
};

void qmapcontrol::GeometryConnectorMapExtention::qt_static_metacall(
    QObject* _o, QMetaObject::Call _c, int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<GeometryConnectorMapExtention*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->start();
                break;
            case 1:
                _t->stop((*reinterpret_cast<MapExtention*(*)>(_a[1])));
                break;
            case 2:
                _t->setChecked((*reinterpret_cast<bool(*)>(_a[1])));
                break;
            case 3:
                _t->zoomChanged_((*reinterpret_cast<int(*)>(_a[1])));
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
            case 1:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<MapExtention*>();
                        break;
                }
                break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::GeometryConnectorMapExtention::staticMetaObject = {
        {&qmapcontrol::CheckableMapExtention::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention.data,
         qt_meta_data_qmapcontrol__GeometryConnectorMapExtention,
         qt_static_metacall, nullptr, nullptr}};

const QMetaObject* qmapcontrol::GeometryConnectorMapExtention::metaObject()
    const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::GeometryConnectorMapExtention::qt_metacast(
    const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_qmapcontrol__GeometryConnectorMapExtention
                    .stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::CheckableMapExtention::qt_metacast(_clname);
}

int qmapcontrol::GeometryConnectorMapExtention::qt_metacall(
    QMetaObject::Call _c, int _id, void** _a)
{
    _id = qmapcontrol::CheckableMapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
