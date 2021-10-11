/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 20), // "on_comBUTTON_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 24), // "on_refreshButton_clicked"
QT_MOC_LITERAL(4, 58, 22), // "on_clearButton_clicked"
QT_MOC_LITERAL(5, 81, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(6, 103, 12), // "TimerTimeout"
QT_MOC_LITERAL(7, 116, 28), // "on_pushButtonSetTime_clicked"
QT_MOC_LITERAL(8, 145, 11), // "AnalyzeData"
QT_MOC_LITERAL(9, 157, 8), // "uint8_t*"
QT_MOC_LITERAL(10, 166, 5), // "param"
QT_MOC_LITERAL(11, 172, 11), // "bProtoLen_t"
QT_MOC_LITERAL(12, 184, 9), // "param_len"
QT_MOC_LITERAL(13, 194, 9), // "setupPlot"
QT_MOC_LITERAL(14, 204, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(15, 228, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(16, 252, 20), // "on_Save_File_clicked"
QT_MOC_LITERAL(17, 273, 20), // "BinaryClassification"
QT_MOC_LITERAL(18, 294, 23) // "on_pushButton_4_clicked"

    },
    "MainWindow\0on_comBUTTON_clicked\0\0"
    "on_refreshButton_clicked\0"
    "on_clearButton_clicked\0on_pushButton_clicked\0"
    "TimerTimeout\0on_pushButtonSetTime_clicked\0"
    "AnalyzeData\0uint8_t*\0param\0bProtoLen_t\0"
    "param_len\0setupPlot\0on_pushButton_3_clicked\0"
    "on_pushButton_2_clicked\0on_Save_File_clicked\0"
    "BinaryClassification\0on_pushButton_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    2,   85,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,
      17,    0,   94,    2, 0x08 /* Private */,
      18,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comBUTTON_clicked(); break;
        case 1: _t->on_refreshButton_clicked(); break;
        case 2: _t->on_clearButton_clicked(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->TimerTimeout(); break;
        case 5: _t->on_pushButtonSetTime_clicked(); break;
        case 6: _t->AnalyzeData((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< bProtoLen_t(*)>(_a[2]))); break;
        case 7: _t->setupPlot(); break;
        case 8: _t->on_pushButton_3_clicked(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        case 10: _t->on_Save_File_clicked(); break;
        case 11: { bool _r = _t->BinaryClassification();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->on_pushButton_4_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
