/****************************************************************************
** Meta object code from reading C++ file 'maplocalworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/maplocalworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'maplocalworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__MapLocalWorker_t
{
    QByteArrayData data[10];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                       \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                \
        len,                                                                \
        qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__MapLocalWorker_t, \
                          stringdata0)                                      \
                 + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__MapLocalWorker_t
    qt_meta_stringdata_qmapcontrol__MapLocalWorker = {
        {
            QT_MOC_LITERAL(0, 0, 27),   // "qmapcontrol::MapLocalWorker"
            QT_MOC_LITERAL(1, 28, 10),  // "fileLoaded"
            QT_MOC_LITERAL(2, 39, 0),   // ""
            QT_MOC_LITERAL(3, 40, 6),   // "pixmap"
            QT_MOC_LITERAL(4, 47, 1),   // "x"
            QT_MOC_LITERAL(5, 49, 1),   // "y"
            QT_MOC_LITERAL(6, 51, 1),   // "z"
            QT_MOC_LITERAL(7, 53, 9),   // "loadError"
            QT_MOC_LITERAL(8, 63, 5),   // "start"
            QT_MOC_LITERAL(9, 69, 9)    // "loadImage"

        },
        "qmapcontrol::MapLocalWorker\0fileLoaded\0"
        "\0pixmap\0x\0y\0z\0loadError\0start\0loadImage"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__MapLocalWorker[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    4, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    2,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 4, 34, 2, 0x06 /* Public */, 7, 3, 43, 2, 0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    8, 0, 50, 2, 0x0a /* Public */, 9, 3, 51, 2, 0x0a /* Public */,

    // signals: parameters
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, 3, 4, 5, 6, QMetaType::Void, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, 4, 5, 6,

    // slots: parameters
    QMetaType::Void, QMetaType::Void, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, 4, 5, 6,

    0  // eod
};

void qmapcontrol::MapLocalWorker::qt_static_metacall(QObject* _o,
                                                     QMetaObject::Call _c,
                                                     int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<MapLocalWorker*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->fileLoaded((*reinterpret_cast<const QPixmap(*)>(_a[1])),
                               (*reinterpret_cast<int(*)>(_a[2])),
                               (*reinterpret_cast<int(*)>(_a[3])),
                               (*reinterpret_cast<int(*)>(_a[4])));
                break;
            case 1:
                _t->loadError((*reinterpret_cast<int(*)>(_a[1])),
                              (*reinterpret_cast<int(*)>(_a[2])),
                              (*reinterpret_cast<int(*)>(_a[3])));
                break;
            case 2:
                _t->start();
                break;
            case 3:
                _t->loadImage((*reinterpret_cast<int(*)>(_a[1])),
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
            using _t = void (MapLocalWorker::*)(const QPixmap, int, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapLocalWorker::fileLoaded))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MapLocalWorker::*)(int, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapLocalWorker::loadError))
            {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::MapLocalWorker::staticMetaObject = {
        {&QObject::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__MapLocalWorker.data,
         qt_meta_data_qmapcontrol__MapLocalWorker, qt_static_metacall, nullptr,
         nullptr}};

const QMetaObject* qmapcontrol::MapLocalWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::MapLocalWorker::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_qmapcontrol__MapLocalWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::MapLocalWorker::qt_metacall(QMetaObject::Call _c, int _id,
                                             void** _a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::MapLocalWorker::fileLoaded(const QPixmap _t1, int _t2,
                                             int _t3, int _t4)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t4))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::MapLocalWorker::loadError(int _t1, int _t2, int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
