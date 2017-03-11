/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[15];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "displayImage"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "captureImage"
QT_MOC_LITERAL(4, 38, 9), // "saveImage"
QT_MOC_LITERAL(5, 48, 3), // "tab"
QT_MOC_LITERAL(6, 52, 4), // "open"
QT_MOC_LITERAL(7, 57, 12), // "QImage2cvMat"
QT_MOC_LITERAL(8, 70, 3), // "Mat"
QT_MOC_LITERAL(9, 74, 5), // "color"
QT_MOC_LITERAL(10, 80, 4), // "Mat&"
QT_MOC_LITERAL(11, 85, 8), // "erode_me"
QT_MOC_LITERAL(12, 94, 6), // "ROI_me"
QT_MOC_LITERAL(13, 101, 12), // "cvMat2QImage"
QT_MOC_LITERAL(14, 114, 3) // "mat"

    },
    "MainWindow\0displayImage\0\0captureImage\0"
    "saveImage\0tab\0open\0QImage2cvMat\0Mat\0"
    "color\0Mat&\0erode_me\0ROI_me\0cvMat2QImage\0"
    "mat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x08 /* Private */,
       3,    0,   69,    2, 0x08 /* Private */,
       4,    0,   70,    2, 0x08 /* Private */,
       5,    1,   71,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    1,   75,    2, 0x08 /* Private */,
       9,    2,   78,    2, 0x08 /* Private */,
      11,    2,   83,    2, 0x08 /* Private */,
      12,    3,   88,    2, 0x08 /* Private */,
      13,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void,
    0x80000000 | 8, QMetaType::QImage,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 10,    2,    2,    2,
    QMetaType::QImage, 0x80000000 | 8,   14,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->displayImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 1: _t->captureImage(); break;
        case 2: _t->saveImage(); break;
        case 3: _t->tab((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 4: _t->open(); break;
        case 5: { Mat _r = _t->QImage2cvMat((*reinterpret_cast< QImage(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Mat*>(_a[0]) = _r; }  break;
        case 6: _t->color((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 7: _t->erode_me((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2]))); break;
        case 8: _t->ROI_me((*reinterpret_cast< Mat(*)>(_a[1])),(*reinterpret_cast< Mat(*)>(_a[2])),(*reinterpret_cast< Mat(*)>(_a[3]))); break;
        case 9: { QImage _r = _t->cvMat2QImage((*reinterpret_cast< const Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
