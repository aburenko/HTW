/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   12,   11,   11, 0x0a,
      56,   46,   11,   11, 0x0a,
     115,   80,   11,   11, 0x0a,
     155,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     211,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     277,  275,   11,   11, 0x08,
     303,  275,   11,   11, 0x08,
     329,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     389,   11,   11,   11, 0x08,
     420,   11,   11,   11, 0x08,
     450,   11,   11,   11, 0x08,
     474,   11,   11,   11, 0x08,
     500,   11,   11,   11, 0x08,
     526,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newPerson\0addedNewPerson(Person*)\0"
    "newMedium\0addedNewMedium(Medium*)\0"
    "title,mediumId,personId,personName\0"
    "giveMediumSlot(QString,int,int,QString)\0"
    "on_actionPerson_triggered()\0"
    "on_actionMedium_triggered()\0"
    "on_deleteMediumButton_clicked()\0"
    "on_deletePersonButton_clicked()\0i\0"
    "sectionClickedMedium(int)\0"
    "sectionClickedPerson(int)\0"
    "on_savePersonButton_clicked()\0"
    "on_saveMediumButton_clicked()\0"
    "on_actionRead_from_triggered()\0"
    "on_actionWrite_to_triggered()\0"
    "on_giveButton_clicked()\0"
    "on_returnButton_clicked()\0"
    "on_searchButton_clicked()\0"
    "on_refreshButton_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->addedNewPerson((*reinterpret_cast< Person*(*)>(_a[1]))); break;
        case 1: _t->addedNewMedium((*reinterpret_cast< Medium*(*)>(_a[1]))); break;
        case 2: _t->giveMediumSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->on_actionPerson_triggered(); break;
        case 4: _t->on_actionMedium_triggered(); break;
        case 5: _t->on_deleteMediumButton_clicked(); break;
        case 6: _t->on_deletePersonButton_clicked(); break;
        case 7: _t->sectionClickedMedium((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sectionClickedPerson((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_savePersonButton_clicked(); break;
        case 10: _t->on_saveMediumButton_clicked(); break;
        case 11: _t->on_actionRead_from_triggered(); break;
        case 12: _t->on_actionWrite_to_triggered(); break;
        case 13: _t->on_giveButton_clicked(); break;
        case 14: _t->on_returnButton_clicked(); break;
        case 15: _t->on_searchButton_clicked(); break;
        case 16: _t->on_refreshButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
