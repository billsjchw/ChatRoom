/****************************************************************************
** Meta object code from reading C++ file 'personal_info_window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QChatClient/personal_info_window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personal_info_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PersonalInfoWindow_t {
    QByteArrayData data[10];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PersonalInfoWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PersonalInfoWindow_t qt_meta_stringdata_PersonalInfoWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PersonalInfoWindow"
QT_MOC_LITERAL(1, 19, 12), // "packetToSend"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 6), // "Packet"
QT_MOC_LITERAL(4, 40, 6), // "packet"
QT_MOC_LITERAL(5, 47, 6), // "finish"
QT_MOC_LITERAL(6, 54, 10), // "enableEdit"
QT_MOC_LITERAL(7, 65, 18), // "updatePersonalInfo"
QT_MOC_LITERAL(8, 84, 12), // "handleSubmit"
QT_MOC_LITERAL(9, 97, 18) // "notifySubmitFinish"

    },
    "PersonalInfoWindow\0packetToSend\0\0"
    "Packet\0packet\0finish\0enableEdit\0"
    "updatePersonalInfo\0handleSubmit\0"
    "notifySubmitFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonalInfoWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    0,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   48,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void PersonalInfoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PersonalInfoWindow *_t = static_cast<PersonalInfoWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->packetToSend((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 1: _t->finish(); break;
        case 2: _t->enableEdit(); break;
        case 3: _t->updatePersonalInfo((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        case 4: _t->handleSubmit(); break;
        case 5: _t->notifySubmitFinish((*reinterpret_cast< Packet(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (PersonalInfoWindow::*_t)(Packet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PersonalInfoWindow::packetToSend)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PersonalInfoWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PersonalInfoWindow::finish)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PersonalInfoWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PersonalInfoWindow.data,
      qt_meta_data_PersonalInfoWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PersonalInfoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonalInfoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonalInfoWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PersonalInfoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PersonalInfoWindow::packetToSend(Packet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PersonalInfoWindow::finish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
