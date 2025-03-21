/****************************************************************************
** Meta object code from reading C++ file 'paramNet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../settings/paramNet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#    error "The header file 'paramNet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#    error "This file was generated using the moc from 5.12.9. It"
#    error "cannot be used with the include files from this version of Qt."
#    error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_paramNet_t
{
    QByteArrayData data[11];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len)                                      \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(               \
        len, qptrdiff(offsetof(qt_meta_stringdata_paramNet_t, stringdata0) \
                      + ofs - idx * sizeof(QByteArrayData)))
static const qt_meta_stringdata_paramNet_t qt_meta_stringdata_paramNet = {
    {
        QT_MOC_LITERAL(0, 0, 8),     // "paramNet"
        QT_MOC_LITERAL(1, 9, 21),    // "updateVectorAntSystem"
        QT_MOC_LITERAL(2, 31, 0),    // ""
        QT_MOC_LITERAL(3, 32, 19),   // "QVector<antSystem>&"
        QT_MOC_LITERAL(4, 52, 10),   // "antSystems"
        QT_MOC_LITERAL(5, 63, 18),   // "updateVectorSender"
        QT_MOC_LITERAL(6, 82, 32),   // "QVector<structParamNet::sender>&"
        QT_MOC_LITERAL(7, 115, 4),   // "send"
        QT_MOC_LITERAL(8, 120, 19),  // "updateVectorRecvier"
        QT_MOC_LITERAL(9, 140, 17),  // "QVector<recvier>&"
        QT_MOC_LITERAL(10, 158, 5)   // "recvs"

    },
    "paramNet\0updateVectorAntSystem\0\0"
    "QVector<antSystem>&\0antSystems\0"
    "updateVectorSender\0QVector<structParamNet::sender>&\0"
    "send\0updateVectorRecvier\0QVector<recvier>&\0"
    "recvs"};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_paramNet[] = {

    // content:
    8,      // revision
    0,      // classname
    0, 0,   // classinfo
    3, 14,  // methods
    0, 0,   // properties
    0, 0,   // enums/sets
    0, 0,   // constructors
    0,      // flags
    3,      // signalCount

    // signals: name, argc, parameters, tag, flags
    1, 1, 29, 2, 0x06 /* Public */, 5, 1, 32, 2, 0x06 /* Public */, 8, 1, 35, 2,
    0x06 /* Public */,

    // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 4, QMetaType::Void, 0x80000000 | 6, 7,
    QMetaType::Void, 0x80000000 | 9, 10,

    0  // eod
};

void paramNet::qt_static_metacall(QObject* _o, QMetaObject::Call _c, int _id,
                                  void** _a)
{
    if (_c == QMetaObject::InvokeMetaMethod)
    {
        auto* _t = static_cast<paramNet*>(_o);
        Q_UNUSED(_t)
        switch (_id)
        {
            case 0:
                _t->updateVectorAntSystem(
                    (*reinterpret_cast<QVector<antSystem>(*)>(_a[1])));
                break;
            case 1:
                _t->updateVectorSender(
                    (*reinterpret_cast<QVector<structParamNet::sender>(*)>(
                        _a[1])));
                break;
            case 2:
                _t->updateVectorRecvier(
                    (*reinterpret_cast<QVector<recvier>(*)>(_a[1])));
                break;
            default:;
        }
    }
    else if (_c == QMetaObject::IndexOfMethod)
    {
        int* result = reinterpret_cast<int*>(_a[0]);
        {
            using _t = void (paramNet::*)(QVector<antSystem>&);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&paramNet::updateVectorAntSystem))
            {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (paramNet::*)(QVector<structParamNet::sender>&);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&paramNet::updateVectorSender))
            {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (paramNet::*)(QVector<recvier>&);
            if (*reinterpret_cast<_t*>(_a[1])
                == static_cast<_t>(&paramNet::updateVectorRecvier))
            {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject paramNet::staticMetaObject = {
    {&QWidget::staticMetaObject, qt_meta_stringdata_paramNet.data,
     qt_meta_data_paramNet, qt_static_metacall, nullptr, nullptr}};

const QMetaObject* paramNet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject()
                                      : &staticMetaObject;
}

void* paramNet::qt_metacast(const char* _clname)
{
    if (!_clname)
        return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_paramNet.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int paramNet::qt_metacall(QMetaObject::Call _c, int _id, void** _a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void paramNet::updateVectorAntSystem(QVector<antSystem>& _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void paramNet::updateVectorSender(QVector<structParamNet::sender>& _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void paramNet::updateVectorRecvier(QVector<recvier>& _t1)
{
    void* _a[] = {nullptr,
                  const_cast<void*>(reinterpret_cast<const void*>(&_t1))};
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
