/****************************************************************************
** Meta object code from reading C++ file 'map_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../map_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'map_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_track__MapWidget_t
{
    QByteArrayData data[13];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                         \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                  \
        len,                                                                  \
        qptrdiff(offsetof(qt_meta_stringdata_track__MapWidget_t, stringdata0) \
                 + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_track__MapWidget_t
    qt_meta_stringdata_track__MapWidget = {
        {
            QT_MOC_LITERAL(0, 0, 16),    // "track::MapWidget"
            QT_MOC_LITERAL(1, 17, 21),   // "MouseDoubleClickEvent"
            QT_MOC_LITERAL(2, 39, 0),    // ""
            QT_MOC_LITERAL(3, 40, 12),   // "QMouseEvent*"
            QT_MOC_LITERAL(4, 53, 4),    // "evnt"
            QT_MOC_LITERAL(5, 58, 10),   // "coordinate"
            QT_MOC_LITERAL(6, 69, 15),   // "loadingFinished"
            QT_MOC_LITERAL(7, 85, 14),   // "MouseMoveEvent"
            QT_MOC_LITERAL(8, 100, 18),  // "const QMouseEvent*"
            QT_MOC_LITERAL(9, 119, 8),   // "tile_get"
            QT_MOC_LITERAL(10, 128, 6),  // "pixmap"
            QT_MOC_LITERAL(11, 135, 1),  // "x"
            QT_MOC_LITERAL(12, 137, 1)   // "y"

        },
        "track::MapWidget\0MouseDoubleClickEvent\0"
        "\0QMouseEvent*\0evnt\0coordinate\0"
        "loadingFinished\0MouseMoveEvent\0"
        "const QMouseEvent*\0tile_get\0pixmap\0x\0"
        "y"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_track__MapWidget[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    4, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    3,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 2, 34, 2, 0x06 /* Public */, 6, 0, 39, 2, 0x06 /* Public */, 7, 2, 40, 2,
    0x06 /* Public */,

    // slots: name, argc, parameters, tag, flags
    9, 3, 45, 2, 0x08 /* Private */,

    // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF, 4, 5, QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, QMetaType::QPointF, 4, 5,

    // slots: parameters
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int, QMetaType::Int, 10, 11,
    12,

    0  // eod
};

void track::MapWidget::qt_static_metacall(QObject* _o, QMetaObject::Call _c,
                                          int _id, void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<MapWidget*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->MouseDoubleClickEvent(
                    (*reinterpret_cast<QMouseEvent*(*)>(_a[1])),
                    (*reinterpret_cast<QPointF(*)>(_a[2])));
                break;
            case 1:
                _t->loadingFinished();
                break;
            case 2:
                _t->MouseMoveEvent(
                    (*reinterpret_cast<const QMouseEvent*(*)>(_a[1])),
                    (*reinterpret_cast<const QPointF(*)>(_a[2])));
                break;
            case 3:
                _t->tile_get((*reinterpret_cast<const QPixmap(*)>(_a[1])),
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
            using _t = void (MapWidget::*)(QMouseEvent*, QPointF);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapWidget::MouseDoubleClickEvent))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MapWidget::*)();
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapWidget::loadingFinished))
            {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MapWidget::*)(const QMouseEvent*, const QPointF);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&MapWidget::MouseMoveEvent))
            {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject track::MapWidget::staticMetaObject = {
    {&qmapcontrol::MapControl::staticMetaObject,
     qt_meta_stringdata_track__MapWidget.data, qt_meta_data_track__MapWidget,
     qt_static_metacall, nullptr, nullptr}};

const QMetaObject* track::MapWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* track::MapWidget::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_track__MapWidget.stringdata0))
        return static_cast<void*>(this);
    return qmapcontrol::MapControl::qt_metacast(_clname);
}

int track::MapWidget::qt_metacall(QMetaObject::Call _c, int _id, void** _a)
{
    _id = qmapcontrol::MapControl::qt_metacall(_c, _id, _a);
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
void track::MapWidget::MouseDoubleClickEvent(QMouseEvent* _t1, QPointF _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void track::MapWidget::loadingFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void track::MapWidget::MouseMoveEvent(const QMouseEvent* _t1, const QPointF _t2)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1)),
                  const_cast<void*>(reinterpret_cast<const void*>(&_t2))};
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
