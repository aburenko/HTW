/****************************************************************************
** Meta object code from reading C++ file 'addnewperson.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "addnewperson.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addnewperson.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddNewPerson[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   13,   13,   13, 0x08,
      77,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddNewPerson[] = {
    "AddNewPerson\0\0newPerson\0"
    "newPersonSignal(Person*)\0"
    "on_completeButton_clicked()\0"
    "on_cancelButton_clicked()\0"
};

void AddNewPerson::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddNewPerson *_t = static_cast<AddNewPerson *>(_o);
        switch (_id) {
        case 0: _t->newPersonSignal((*reinterpret_cast< Person*(*)>(_a[1]))); break;
        case 1: _t->on_completeButton_clicked(); break;
        case 2: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddNewPerson::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddNewPerson::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddNewPerson,
      qt_meta_data_AddNewPerson, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddNewPerson::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddNewPerson::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddNewPerson::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddNewPerson))
        return static_cast<void*>(const_cast< AddNewPerson*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddNewPerson::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AddNewPerson::newPersonSignal(Person * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
