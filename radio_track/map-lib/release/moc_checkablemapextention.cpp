/****************************************************************************
** Meta object code from reading C++ file 'checkablemapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/checkablemapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error \
        "The header file 'checkablemapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__CheckableMapExtention_t
{
    QByteArrayData data[12];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                         \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                  \
        len,                                                                  \
        qptrdiff(                                                             \
            offsetof(qt_meta_stringdata_qmapcontrol__CheckableMapExtention_t, \
                     stringdata0)                                             \
            + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__CheckableMapExtention_t
    qt_meta_stringdata_qmapcontrol__CheckableMapExtention = {
        {
            QT_MOC_LITERAL(0, 0, 34),     // "qmapcontrol::CheckableMapExte..."
            QT_MOC_LITERAL(1, 35, 14),    // "checkedChanged"
            QT_MOC_LITERAL(2, 50, 0),     // ""
            QT_MOC_LITERAL(3, 51, 7),     // "checked"
            QT_MOC_LITERAL(4, 59, 5),     // "start"
            QT_MOC_LITERAL(5, 65, 4),     // "stop"
            QT_MOC_LITERAL(6, 70, 13),    // "MapExtention*"
            QT_MOC_LITERAL(7, 84, 6),     // "sender"
            QT_MOC_LITERAL(8, 91, 10),    // "setChecked"
            QT_MOC_LITERAL(9, 102, 14),   // "keyboardEvent_"
            QT_MOC_LITERAL(10, 117, 16),  // "const QKeyEvent*"
            QT_MOC_LITERAL(11, 134, 5)    // "event"

        },
        "qmapcontrol::CheckableMapExtention\0"
        "checkedChanged\0\0checked\0start\0stop\0"
        "MapExtention*\0sender\0setChecked\0"
        "keyboardEvent_\0const QKeyEvent*\0event"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__CheckableMapExtention[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    5, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    1,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 1, 39, 2, 0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    4, 0, 42, 2, 0x0a /* Public */, 5, 1, 43, 2, 0x0a /* Public */, 8, 1, 46, 2,
    0x0a /* Public */, 9, 1, 49, 2, 0x08 /* Private */,

    // signals: parameters
    QMetaType::Void, QMetaType::Bool, 3,

    // slots: parameters
    QMetaType::Void, QMetaType::Void, 0x80000000 | 6, 7, QMetaType::Void,
    QMetaType::Bool, 3, QMetaType::Void, 0x80000000 | 10, 11,

    0  // eod
};

void qmapcontrol::CheckableMapExtention::qt_static_metacall(
    QObject* _o, QMetaObject::Call _c, int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<CheckableMapExtention*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->checkedChanged((*reinterpret_cast<bool(*)>(_a[1])));
                break;
            case 1:
                _t->start();
                break;
            case 2:
                _t->stop((*reinterpret_cast<MapExtention*(*)>(_a[1])));
                break;
            case 3:
                _t->setChecked((*reinterpret_cast<bool(*)>(_a[1])));
                break;
            case 4:
                _t->keyboardEvent_(
                    (*reinterpret_cast<const QKeyEvent*(*)>(_a[1])));
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
            case 2:
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
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (CheckableMapExtention::*)(bool);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&CheckableMapExtention::checkedChanged))
            {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::CheckableMapExtention::staticMetaObject = {
        {&MapExtention::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__CheckableMapExtention.data,
         qt_meta_data_qmapcontrol__CheckableMapExtention, qt_static_metacall,
         nullptr, nullptr}};

const QMetaObject* qmapcontrol::CheckableMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::CheckableMapExtention::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(
            _clname,
            qt_meta_stringdata_qmapcontrol__CheckableMapExtention.stringdata0))
        return static_cast<void*>(this);
    return MapExtention::qt_metacast(_clname);
}

int qmapcontrol::CheckableMapExtention::qt_metacall(QMetaObject::Call _c,
                                                    int _id, void** _a)
{
    _id = MapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::CheckableMapExtention::checkedChanged(bool _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
