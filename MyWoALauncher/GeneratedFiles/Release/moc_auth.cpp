/****************************************************************************
** Meta object code from reading C++ file 'auth.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../auth.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auth.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_auth_t {
    QByteArrayData data[20];
    char stringdata0[349];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_auth_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_auth_t qt_meta_stringdata_auth = {
    {
QT_MOC_LITERAL(0, 0, 4), // "auth"
QT_MOC_LITERAL(1, 5, 17), // "signal_start_game"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 23), // "signal_disable_controls"
QT_MOC_LITERAL(4, 48, 29), // "signal_notify_ui_game_started"
QT_MOC_LITERAL(5, 78, 28), // "signal_notify_ui_game_closed"
QT_MOC_LITERAL(6, 107, 24), // "signal_send_tray_message"
QT_MOC_LITERAL(7, 132, 18), // "signal_send_status"
QT_MOC_LITERAL(8, 151, 15), // "wss_onConnected"
QT_MOC_LITERAL(9, 167, 18), // "wss_onDisconnected"
QT_MOC_LITERAL(10, 186, 25), // "wss_onTextMessageReceived"
QT_MOC_LITERAL(11, 212, 7), // "message"
QT_MOC_LITERAL(12, 220, 11), // "onSslErrors"
QT_MOC_LITERAL(13, 232, 16), // "QList<QSslError>"
QT_MOC_LITERAL(14, 249, 6), // "errors"
QT_MOC_LITERAL(15, 256, 11), // "wss_onError"
QT_MOC_LITERAL(16, 268, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(17, 297, 5), // "error"
QT_MOC_LITERAL(18, 303, 15), // "slot_start_game"
QT_MOC_LITERAL(19, 319, 29) // "slot_collect_digest_post_game"

    },
    "auth\0signal_start_game\0\0signal_disable_controls\0"
    "signal_notify_ui_game_started\0"
    "signal_notify_ui_game_closed\0"
    "signal_send_tray_message\0signal_send_status\0"
    "wss_onConnected\0wss_onDisconnected\0"
    "wss_onTextMessageReceived\0message\0"
    "onSslErrors\0QList<QSslError>\0errors\0"
    "wss_onError\0QAbstractSocket::SocketError\0"
    "error\0slot_start_game\0"
    "slot_collect_digest_post_game"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_auth[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,
       4,    0,   85,    2, 0x06 /* Public */,
       5,    0,   86,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   93,    2, 0x0a /* Public */,
       9,    0,   94,    2, 0x0a /* Public */,
      10,    1,   95,    2, 0x0a /* Public */,
      12,    1,   98,    2, 0x0a /* Public */,
      15,    1,  101,    2, 0x0a /* Public */,
      18,    1,  104,    2, 0x0a /* Public */,
      19,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void auth::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auth *_t = static_cast<auth *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_start_game((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signal_disable_controls((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->signal_notify_ui_game_started(); break;
        case 3: _t->signal_notify_ui_game_closed(); break;
        case 4: _t->signal_send_tray_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->signal_send_status((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->wss_onConnected(); break;
        case 7: _t->wss_onDisconnected(); break;
        case 8: _t->wss_onTextMessageReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onSslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 10: _t->wss_onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->slot_start_game((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->slot_collect_digest_post_game(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (auth::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_start_game)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (auth::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_disable_controls)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (auth::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_notify_ui_game_started)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (auth::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_notify_ui_game_closed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (auth::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_send_tray_message)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (auth::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&auth::signal_send_status)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject auth::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_auth.data,
      qt_meta_data_auth,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *auth::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *auth::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_auth.stringdata0))
        return static_cast<void*>(const_cast< auth*>(this));
    return QObject::qt_metacast(_clname);
}

int auth::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void auth::signal_start_game(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void auth::signal_disable_controls(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void auth::signal_notify_ui_game_started()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void auth::signal_notify_ui_game_closed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void auth::signal_send_tray_message(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void auth::signal_send_status(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
