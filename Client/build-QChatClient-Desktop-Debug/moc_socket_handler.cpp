/****************************************************************************
** Meta object code from reading C++ file 'socket_handler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QChatClient/socket_handler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socket_handler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SocketHandler_t {
    QByteArrayData data[9];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SocketHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SocketHandler_t qt_meta_stringdata_SocketHandler = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SocketHandler"
QT_MOC_LITERAL(1, 14, 6), // "newMsg"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "Packet"
QT_MOC_LITERAL(4, 29, 6), // "packet"
QT_MOC_LITERAL(5, 36, 11), // "setInfoResp"
QT_MOC_LITERAL(6, 48, 15), // "basicInfoChange"
QT_MOC_LITERAL(7, 64, 13), // "receivePacket"
QT_MOC_LITERAL(8, 78, 10) // "sendPacket"

    },
    "SocketHandler\0newMsg\0\0Packet\0packet\0"
    "setInfoResp\0basicInfoChange\0receivePacket\0"
    "sendPacket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SocketHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   48,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void SocketHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SocketHandler *_t = static_cast<SocketHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMsg((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 1: _t->setInfoResp((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 2: _t->basicInfoChange((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 3: _t->receivePacket(); break;
        case 4: _t->sendPacket((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (SocketHandler::*_t)(Packet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketHandler::newMsg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SocketHandler::*_t)(Packet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketHandler::setInfoResp)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SocketHandler::*_t)(Packet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SocketHandler::basicInfoChange)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject SocketHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SocketHandler.data,
      qt_meta_data_SocketHandler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SocketHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SocketHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SocketHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SocketHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SocketHandler::newMsg(Packet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SocketHandler::setInfoResp(Packet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SocketHandler::basicInfoChange(Packet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
