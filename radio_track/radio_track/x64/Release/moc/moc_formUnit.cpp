/****************************************************************************
** Meta object code from reading C++ file 'formUnit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../settings/formUnit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'formUnit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_unitWindow_t
{
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                        \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(                 \
        len, qptrdiff(offsetof(qt_meta_stringdata_unitWindow_t, stringdata0) \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_unitWindow_t qt_meta_stringdata_unitWindow = {
    {
        QT_MOC_LITERAL(0, 0, 10),   // "unitWindow"
        QT_MOC_LITERAL(1, 11, 11),  // "unitCreated"
        QT_MOC_LITERAL(2, 23, 0),   // ""
        QT_MOC_LITERAL(3, 24, 4),   // "unit"
        QT_MOC_LITERAL(4, 29, 10)   // "unitUpdate"

    },
    "unitWindow\0unitCreated\0\0unit\0unitUpdate"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_unitWindow[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    2, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    2,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 1, 24, 2, 0x06 /* Public */, 4, 1, 27, 2, 0x06 /* Public */,

    // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 3, QMetaType::Void, 0x80000000 | 3, 3,

    0  // eod
};

void unitWindow::qt_static_metacall(QObject* _o, QMetaObject::Call _c, int _id,
                                    void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<unitWindow*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->unitCreated((*reinterpret_cast<unit(*)>(_a[1])));
                break;
            case 1:
                _t->unitUpdate((*reinterpret_cast<unit(*)>(_a[1])));
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
            case 0:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<unit>();
                        break;
                }
                break;
            case 1:
                switch (*reinterpret_cast<int*>(_a[1]))
                {
                    default:
                        *reinterpret_cast<int*>(_a[0]) = -1;
                        break;
                    case 0:
                        *reinterpret_cast<int*>(_a[0]) =
                            qRegisterMetaType<unit>();
                        break;
                }
                break;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (unitWindow::*)(unit);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&unitWindow::unitCreated))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (unitWindow::*)(unit);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&unitWindow::unitUpdate))
            {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject unitWindow::staticMetaObject = {
    {&QWidget::staticMetaObject, qt_meta_stringdata_unitWindow.data,
     qt_meta_data_unitWindow, qt_static_metacall, nullptr, nullptr}};

const QMetaObject* unitWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* unitWindow::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_unitWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int unitWindow::qt_metacall(QMetaObject::Call _c, int _id, void** _a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    else if (_c == QMetaObject::RegisterMethodArgumentMetaType)
    {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void unitWindow::unitCreated(unit _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void unitWindow::unitUpdate(unit _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
