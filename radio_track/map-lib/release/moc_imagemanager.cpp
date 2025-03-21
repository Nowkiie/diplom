/****************************************************************************
** Meta object code from reading C++ file 'imagemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/core/imagemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'imagemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__ImageManager_t
{
    QByteArrayData data[11];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                          \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                   \
        len, qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__ImageManager_t, \
                               stringdata0)                                    \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_qmapcontrol__ImageManager_t
    qt_meta_stringdata_qmapcontrol__ImageManager = {
        {
            QT_MOC_LITERAL(0, 0, 25),   // "qmapcontrol::ImageManager"
            QT_MOC_LITERAL(1, 26, 13),  // "imageReceived"
            QT_MOC_LITERAL(2, 40, 0),   // ""
            QT_MOC_LITERAL(3, 41, 1),   // "x"
            QT_MOC_LITERAL(4, 43, 1),   // "y"
            QT_MOC_LITERAL(5, 45, 1),   // "z"
            QT_MOC_LITERAL(6, 47, 15),  // "loadingFinished"
            QT_MOC_LITERAL(7, 63, 11),  // "imageLoaded"
            QT_MOC_LITERAL(8, 75, 6),   // "pixmap"
            QT_MOC_LITERAL(9, 82, 10),  // "imageEmpty"
            QT_MOC_LITERAL(10, 93, 21)  // "imageLoadingComplited"

        },
        "qmapcontrol::ImageManager\0imageReceived\0"
        "\0x\0y\0z\0loadingFinished\0imageLoaded\0"
        "pixmap\0imageEmpty\0imageLoadingComplited"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__ImageManager[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    5, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    2,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 3, 39, 2, 0x06 /* Public */, 6, 0, 46, 2, 0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    7, 4, 47, 2, 0x08 /* Private */, 9, 3, 56, 2, 0x08 /* Private */, 10, 0, 63,
    2, 0x08 /* Private */,

    // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, 3, 4, 5,
    QMetaType::Void,

    // slots: parameters
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, 8, 3, 4, 5, QMetaType::Void, QMetaType::Int, QMetaType::Int,
    QMetaType::Int, 3, 4, 5, QMetaType::Void,

    0  // eod
};

void qmapcontrol::ImageManager::qt_static_metacall(QObject* _o,
                                                   QMetaObject::Call _c,
                                                   int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<ImageManager*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->imageReceived((*reinterpret_cast<int(*)>(_a[1])),
                                  (*reinterpret_cast<int(*)>(_a[2])),
                                  (*reinterpret_cast<int(*)>(_a[3])));
                break;
            case 1:
                _t->loadingFinished();
                break;
            case 2:
                _t->imageLoaded((*reinterpret_cast<const QPixmap(*)>(_a[1])),
                                (*reinterpret_cast<int(*)>(_a[2])),
                                (*reinterpret_cast<int(*)>(_a[3])),
                                (*reinterpret_cast<int(*)>(_a[4])));
                break;
            case 3:
                _t->imageEmpty((*reinterpret_cast<int(*)>(_a[1])),
                               (*reinterpret_cast<int(*)>(_a[2])),
                               (*reinterpret_cast<int(*)>(_a[3])));
                break;
            case 4:
                _t->imageLoadingComplited();
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (ImageManager::*)(int, int, int);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&ImageManager::imageReceived))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageManager::*)();
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&ImageManager::loadingFinished))
            {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject
    qmapcontrol::ImageManager::staticMetaObject = {
        {&QObject::staticMetaObject,
         qt_meta_stringdata_qmapcontrol__ImageManager.data,
         qt_meta_data_qmapcontrol__ImageManager, qt_static_metacall, nullptr,
         nullptr}};

const QMetaObject* qmapcontrol::ImageManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* qmapcontrol::ImageManager::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname,
                qt_meta_stringdata_qmapcontrol__ImageManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int qmapcontrol::ImageManager::qt_metacall(QMetaObject::Call _c, int _id,
                                           void** _a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::ImageManager::imageReceived(int _t1, int _t2, int _t3)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t3))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::ImageManager::loadingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
