/****************************************************************************
** Meta object code from reading C++ file 'cursorposmapextention.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../submodules/BaseMap/extentions/cursorposmapextention.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cursorposmapextention.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_qmapcontrol__CursorPosMapExtention_t {
    QByteArrayData data[8];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_qmapcontrol__CursorPosMapExtention_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_qmapcontrol__CursorPosMapExtention_t qt_meta_stringdata_qmapcontrol__CursorPosMapExtention = {
    {
QT_MOC_LITERAL(0, 0, 34), // "qmapcontrol::CursorPosMapExte..."
QT_MOC_LITERAL(1, 35, 9), // "cursorPos"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 8), // "position"
QT_MOC_LITERAL(4, 55, 21), // "mouseEventCoordinate_"
QT_MOC_LITERAL(5, 77, 18), // "const QMouseEvent*"
QT_MOC_LITERAL(6, 96, 4), // "evnt"
QT_MOC_LITERAL(7, 101, 10) // "coordinate"

    },
    "qmapcontrol::CursorPosMapExtention\0"
    "cursorPos\0\0position\0mouseEventCoordinate_\0"
    "const QMouseEvent*\0evnt\0coordinate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_qmapcontrol__CursorPosMapExtention[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       1,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::QPointF,    6,    7,

       0        // eod
};

void qmapcontrol::CursorPosMapExtention::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CursorPosMapExtention *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cursorPos((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->cursorPos((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->mouseEventCoordinate_((*reinterpret_cast< const QMouseEvent*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CursorPosMapExtention::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CursorPosMapExtention::cursorPos)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CursorPosMapExtention::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CursorPosMapExtention::cursorPos)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject qmapcontrol::CursorPosMapExtention::staticMetaObject = { {
    &PersistentMapExtention::staticMetaObject,
    qt_meta_stringdata_qmapcontrol__CursorPosMapExtention.data,
    qt_meta_data_qmapcontrol__CursorPosMapExtention,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *qmapcontrol::CursorPosMapExtention::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qmapcontrol::CursorPosMapExtention::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_qmapcontrol__CursorPosMapExtention.stringdata0))
        return static_cast<void*>(this);
    return PersistentMapExtention::qt_metacast(_clname);
}

int qmapcontrol::CursorPosMapExtention::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PersistentMapExtention::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void qmapcontrol::CursorPosMapExtention::cursorPos(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void qmapcontrol::CursorPosMapExtention::cursorPos(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
