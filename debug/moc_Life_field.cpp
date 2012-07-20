/****************************************************************************
** Meta object code from reading C++ file 'Life_field.h'
**
** Created: Thu Jul 19 20:55:27 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Life_field.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Life_field.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LifeField[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      28,   10,   10,   10, 0x0a,
      36,   10,   10,   10, 0x0a,
      55,   10,   10,   10, 0x0a,
      73,   10,   10,   10, 0x0a,
      83,   10,   10,   10, 0x0a,
      95,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LifeField[] = {
    "LifeField\0\0nextGeneration()\0clear()\0"
    "startGenerations()\0stopGenerations()\0"
    "setFast()\0setNormal()\0setSlow()\0"
};

void LifeField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LifeField *_t = static_cast<LifeField *>(_o);
        switch (_id) {
        case 0: _t->nextGeneration(); break;
        case 1: _t->clear(); break;
        case 2: _t->startGenerations(); break;
        case 3: _t->stopGenerations(); break;
        case 4: _t->setFast(); break;
        case 5: _t->setNormal(); break;
        case 6: _t->setSlow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LifeField::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LifeField::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LifeField,
      qt_meta_data_LifeField, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LifeField::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LifeField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LifeField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LifeField))
        return static_cast<void*>(const_cast< LifeField*>(this));
    return QWidget::qt_metacast(_clname);
}

int LifeField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
