/****************************************************************************
** Meta object code from reading C++ file 'addnewmedium.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "addnewmedium.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addnewmedium.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddNewMedium[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   13,   13,   13, 0x08,
      76,   13,   13,   13, 0x08,
     105,   13,   13,   13, 0x08,
     133,   13,   13,   13, 0x08,
     156,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddNewMedium[] = {
    "AddNewMedium\0\0newMedium\0"
    "newMediumSignal(Medium*)\0"
    "on_radioButtonCD_clicked()\0"
    "on_radioButtonBook_clicked()\0"
    "on_radioButtonDVD_clicked()\0"
    "on_addButton_clicked()\0on_cancelButton_clicked()\0"
};

void AddNewMedium::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddNewMedium *_t = static_cast<AddNewMedium *>(_o);
        switch (_id) {
        case 0: _t->newMediumSignal((*reinterpret_cast< Medium*(*)>(_a[1]))); break;
        case 1: _t->on_radioButtonCD_clicked(); break;
        case 2: _t->on_radioButtonBook_clicked(); break;
        case 3: _t->on_radioButtonDVD_clicked(); break;
        case 4: _t->on_addButton_clicked(); break;
        case 5: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddNewMedium::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddNewMedium::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddNewMedium,
      qt_meta_data_AddNewMedium, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddNewMedium::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddNewMedium::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddNewMedium::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddNewMedium))
        return static_cast<void*>(const_cast< AddNewMedium*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddNewMedium::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AddNewMedium::newMediumSignal(Medium * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
