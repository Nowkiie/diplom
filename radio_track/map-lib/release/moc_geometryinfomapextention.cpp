/****************************************************************************
** Meta object code from reading C++ file 'geometryinfomapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/geometryinfomapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error \
        "The header file 'geometryinfomapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GeometryInfoMapExtention_t
{
    QByteArrayData data[10];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                         \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                  \
        len, qptrdiff(offsetof(qt_meta_stringdata_GeometryInfoMapExtention_t, \
                               stringdata0)                                   \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_GeometryInfoMapExtention_t
    qt_meta_stringdata_GeometryInfoMapExtention = {
        {
            QT_MOC_LITERAL(0, 0, 24),   // "GeometryInfoMapExtention"
            QT_MOC_LITERAL(1, 25, 5),   // "start"
            QT_MOC_LITERAL(2, 31, 0),   // ""
            QT_MOC_LITERAL(3, 32, 4),   // "stop"
            QT_MOC_LITERAL(4, 37, 13),  // "MapExtention*"
            QT_MOC_LITERAL(5, 51, 6),   // "sender"
            QT_MOC_LITERAL(6, 58, 22),  // "mouseDoubleClickEvent_"
            QT_MOC_LITERAL(7, 81, 12),  // "QMouseEvent*"
            QT_MOC_LITERAL(8, 94, 1),   // "e"
            QT_MOC_LITERAL(9, 96, 10)   // "coordinate"

        },
        "GeometryInfoMapExtention\0start\0\0stop\0"
        "MapExtention*\0sender\0mouseDoubleClickEvent_\0"
        "QMouseEvent*\0e\0coordinate"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeometryInfoMapExtention[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    3, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    0,      // signalCount

    // slots: name, argc, parameters, tag, flags
    1, 0, 29, 2, 0x0a /* Public */, 3, 1, 30, 2, 0x0a /* Public */, 6, 2, 33, 2,
    0x08 /* Private */,

    // slots: parameters
    QMetaType::Void, QMetaType::Void, 0x80000000 | 4, 5, QMetaType::Void,
    0x80000000 | 7, QMetaType::QPointF, 8, 9,

    0  // eod
};

void GeometryInfoMapExtention::qt_static_metacall(QObject* _o,
                                                  QMetaObject::Call _c, int _id,
                                                  void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<GeometryInfoMapExtention*>(_o);
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
                _t->mouseDoubleClickEvent_(
                    (*reinterpret_cast<QMouseEvent*(*)>(_a[1])),
                    (*reinterpret_cast<QPointF(*)>(_a[2])));
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
    GeometryInfoMapExtention::staticMetaObject = {
        {&qmapcontrol::MapExtention::staticMetaObject,
         qt_meta_stringdata_GeometryInfoMapExtention.data,
         qt_meta_data_GeometryInfoMapExtention, qt_static_metacall, nullptr,
         nullptr}};

const QMetaObject* GeometryInfoMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* GeometryInfoMapExtention::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_GeometryInfoMapExtention.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "qmapcontrol::GeometryProcessor"))
        return static_cast<qmapcontrol::GeometryProcessor*>(this);
    return qmapcontrol::MapExtention::qt_metacast(_clname);
}

int GeometryInfoMapExtention::qt_metacall(QMetaObject::Call _c, int _id,
                                          void** _a)
{
    _id = qmapcontrol::MapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
