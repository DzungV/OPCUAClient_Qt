/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
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
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[111];
    char stringdata0[2256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "UpdateTimerTick"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "IOAlarmTick"
QT_MOC_LITERAL(4, 40, 5), // "Clock"
QT_MOC_LITERAL(5, 46, 13), // "ServerTimeout"
QT_MOC_LITERAL(6, 60, 10), // "JogRBTimer"
QT_MOC_LITERAL(7, 71, 8), // "ReadData"
QT_MOC_LITERAL(8, 80, 10), // "UA_Client*"
QT_MOC_LITERAL(9, 91, 6), // "client"
QT_MOC_LITERAL(10, 98, 5), // "Alarm"
QT_MOC_LITERAL(11, 104, 13), // "ReadDeltaData"
QT_MOC_LITERAL(12, 118, 6), // "ReadDI"
QT_MOC_LITERAL(13, 125, 6), // "ReadDO"
QT_MOC_LITERAL(14, 132, 9), // "DisplayDI"
QT_MOC_LITERAL(15, 142, 9), // "DisplayDO"
QT_MOC_LITERAL(16, 152, 10), // "JogProcess"
QT_MOC_LITERAL(17, 163, 6), // "number"
QT_MOC_LITERAL(18, 170, 9), // "SetSttbar"
QT_MOC_LITERAL(19, 180, 4), // "bset"
QT_MOC_LITERAL(20, 185, 11), // "CheckCMDAck"
QT_MOC_LITERAL(21, 197, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(22, 217, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(23, 236, 20), // "on_btnJ1_neg_pressed"
QT_MOC_LITERAL(24, 257, 21), // "on_btnJ1_neg_released"
QT_MOC_LITERAL(25, 279, 20), // "on_btnJ1_pos_pressed"
QT_MOC_LITERAL(26, 300, 21), // "on_btnJ1_pos_released"
QT_MOC_LITERAL(27, 322, 20), // "on_btnJ2_neg_pressed"
QT_MOC_LITERAL(28, 343, 21), // "on_btnJ2_neg_released"
QT_MOC_LITERAL(29, 365, 20), // "on_btnJ2_pos_pressed"
QT_MOC_LITERAL(30, 386, 21), // "on_btnJ2_pos_released"
QT_MOC_LITERAL(31, 408, 20), // "on_btnJ3_neg_pressed"
QT_MOC_LITERAL(32, 429, 21), // "on_btnJ3_neg_released"
QT_MOC_LITERAL(33, 451, 20), // "on_btnJ3_pos_pressed"
QT_MOC_LITERAL(34, 472, 21), // "on_btnJ3_pos_released"
QT_MOC_LITERAL(35, 494, 20), // "on_btnJ4_neg_pressed"
QT_MOC_LITERAL(36, 515, 21), // "on_btnJ4_neg_released"
QT_MOC_LITERAL(37, 537, 20), // "on_btnJ4_pos_pressed"
QT_MOC_LITERAL(38, 558, 21), // "on_btnJ4_pos_released"
QT_MOC_LITERAL(39, 580, 20), // "on_btnJ5_neg_pressed"
QT_MOC_LITERAL(40, 601, 21), // "on_btnJ5_neg_released"
QT_MOC_LITERAL(41, 623, 20), // "on_btnJ5_pos_pressed"
QT_MOC_LITERAL(42, 644, 21), // "on_btnJ5_pos_released"
QT_MOC_LITERAL(43, 666, 20), // "on_btnJ6_neg_pressed"
QT_MOC_LITERAL(44, 687, 21), // "on_btnJ6_neg_released"
QT_MOC_LITERAL(45, 709, 20), // "on_btnJ6_pos_pressed"
QT_MOC_LITERAL(46, 730, 21), // "on_btnJ6_pos_released"
QT_MOC_LITERAL(47, 752, 31), // "on_chbCoords_currentTextChanged"
QT_MOC_LITERAL(48, 784, 4), // "arg1"
QT_MOC_LITERAL(49, 789, 22), // "on_btnSendProg_clicked"
QT_MOC_LITERAL(50, 812, 23), // "on_btnSpeed_low_clicked"
QT_MOC_LITERAL(51, 836, 23), // "on_btnSpeed_med_clicked"
QT_MOC_LITERAL(52, 860, 24), // "on_btnSpeed_high_clicked"
QT_MOC_LITERAL(53, 885, 23), // "on_btnSpeed_top_clicked"
QT_MOC_LITERAL(54, 909, 23), // "on_btnWriteProg_clicked"
QT_MOC_LITERAL(55, 933, 22), // "on_btnCompProg_clicked"
QT_MOC_LITERAL(56, 956, 30), // "on_comboBox_currentTextChanged"
QT_MOC_LITERAL(57, 987, 21), // "on_btnDataAdd_clicked"
QT_MOC_LITERAL(58, 1009, 24), // "on_btnSendPoints_clicked"
QT_MOC_LITERAL(59, 1034, 30), // "on_tabJPointList_1_itemClicked"
QT_MOC_LITERAL(60, 1065, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(61, 1083, 4), // "item"
QT_MOC_LITERAL(62, 1088, 30), // "on_tabWPointList_1_itemClicked"
QT_MOC_LITERAL(63, 1119, 30), // "on_tabJPointList_2_itemClicked"
QT_MOC_LITERAL(64, 1150, 30), // "on_tabJPointList_3_itemClicked"
QT_MOC_LITERAL(65, 1181, 30), // "on_tabJPointList_4_itemClicked"
QT_MOC_LITERAL(66, 1212, 30), // "on_tabWPointList_2_itemClicked"
QT_MOC_LITERAL(67, 1243, 30), // "on_tabWPointList_3_itemClicked"
QT_MOC_LITERAL(68, 1274, 30), // "on_tabWPointList_4_itemClicked"
QT_MOC_LITERAL(69, 1305, 24), // "on_chbDIgr1_stateChanged"
QT_MOC_LITERAL(70, 1330, 24), // "on_chbDIgr2_stateChanged"
QT_MOC_LITERAL(71, 1355, 24), // "on_chbDIgr3_stateChanged"
QT_MOC_LITERAL(72, 1380, 24), // "on_chbDIgr4_stateChanged"
QT_MOC_LITERAL(73, 1405, 24), // "on_chbDIgr5_stateChanged"
QT_MOC_LITERAL(74, 1430, 24), // "on_chbDIgr6_stateChanged"
QT_MOC_LITERAL(75, 1455, 24), // "on_chbDIgr7_stateChanged"
QT_MOC_LITERAL(76, 1480, 24), // "on_chbDIgr8_stateChanged"
QT_MOC_LITERAL(77, 1505, 24), // "on_chbDIgr9_stateChanged"
QT_MOC_LITERAL(78, 1530, 25), // "on_chbDIgr10_stateChanged"
QT_MOC_LITERAL(79, 1556, 21), // "on_btnDataDel_clicked"
QT_MOC_LITERAL(80, 1578, 21), // "on_btnOpenPts_clicked"
QT_MOC_LITERAL(81, 1600, 20), // "on_btnSaveIP_clicked"
QT_MOC_LITERAL(82, 1621, 26), // "on_cbEnableDO_stateChanged"
QT_MOC_LITERAL(83, 1648, 24), // "on_chbDOgr1_stateChanged"
QT_MOC_LITERAL(84, 1673, 24), // "on_chbDOgr2_stateChanged"
QT_MOC_LITERAL(85, 1698, 24), // "on_chbDOgr3_stateChanged"
QT_MOC_LITERAL(86, 1723, 24), // "on_chbDOgr4_stateChanged"
QT_MOC_LITERAL(87, 1748, 24), // "on_chbDOgr5_stateChanged"
QT_MOC_LITERAL(88, 1773, 24), // "on_chbDOgr6_stateChanged"
QT_MOC_LITERAL(89, 1798, 24), // "on_chbDOgr7_stateChanged"
QT_MOC_LITERAL(90, 1823, 24), // "on_chbDOgr8_stateChanged"
QT_MOC_LITERAL(91, 1848, 24), // "on_chbDOgr9_stateChanged"
QT_MOC_LITERAL(92, 1873, 25), // "on_chbDOgr10_stateChanged"
QT_MOC_LITERAL(93, 1899, 17), // "on_btnDO1_toggled"
QT_MOC_LITERAL(94, 1917, 7), // "checked"
QT_MOC_LITERAL(95, 1925, 17), // "on_btnDO2_toggled"
QT_MOC_LITERAL(96, 1943, 17), // "on_btnDO3_toggled"
QT_MOC_LITERAL(97, 1961, 17), // "on_btnDO4_toggled"
QT_MOC_LITERAL(98, 1979, 17), // "on_btnDO5_toggled"
QT_MOC_LITERAL(99, 1997, 17), // "on_btnDO6_toggled"
QT_MOC_LITERAL(100, 2015, 17), // "on_btnDO7_toggled"
QT_MOC_LITERAL(101, 2033, 17), // "on_btnDO8_toggled"
QT_MOC_LITERAL(102, 2051, 32), // "on_combSeclvl_currentTextChanged"
QT_MOC_LITERAL(103, 2084, 20), // "on_btnOkpass_clicked"
QT_MOC_LITERAL(104, 2105, 20), // "on_btnRunprg_clicked"
QT_MOC_LITERAL(105, 2126, 22), // "on_btnPauseprg_clicked"
QT_MOC_LITERAL(106, 2149, 21), // "on_btnStopprg_clicked"
QT_MOC_LITERAL(107, 2171, 20), // "on_btnRBMode_toggled"
QT_MOC_LITERAL(108, 2192, 21), // "on_btnRBCLock_toggled"
QT_MOC_LITERAL(109, 2214, 21), // "on_btnRBServo_toggled"
QT_MOC_LITERAL(110, 2236, 19) // "on_btnSimRB_clicked"

    },
    "MainWindow\0UpdateTimerTick\0\0IOAlarmTick\0"
    "Clock\0ServerTimeout\0JogRBTimer\0ReadData\0"
    "UA_Client*\0client\0Alarm\0ReadDeltaData\0"
    "ReadDI\0ReadDO\0DisplayDI\0DisplayDO\0"
    "JogProcess\0number\0SetSttbar\0bset\0"
    "CheckCMDAck\0on_btnStart_clicked\0"
    "on_btnStop_clicked\0on_btnJ1_neg_pressed\0"
    "on_btnJ1_neg_released\0on_btnJ1_pos_pressed\0"
    "on_btnJ1_pos_released\0on_btnJ2_neg_pressed\0"
    "on_btnJ2_neg_released\0on_btnJ2_pos_pressed\0"
    "on_btnJ2_pos_released\0on_btnJ3_neg_pressed\0"
    "on_btnJ3_neg_released\0on_btnJ3_pos_pressed\0"
    "on_btnJ3_pos_released\0on_btnJ4_neg_pressed\0"
    "on_btnJ4_neg_released\0on_btnJ4_pos_pressed\0"
    "on_btnJ4_pos_released\0on_btnJ5_neg_pressed\0"
    "on_btnJ5_neg_released\0on_btnJ5_pos_pressed\0"
    "on_btnJ5_pos_released\0on_btnJ6_neg_pressed\0"
    "on_btnJ6_neg_released\0on_btnJ6_pos_pressed\0"
    "on_btnJ6_pos_released\0"
    "on_chbCoords_currentTextChanged\0arg1\0"
    "on_btnSendProg_clicked\0on_btnSpeed_low_clicked\0"
    "on_btnSpeed_med_clicked\0"
    "on_btnSpeed_high_clicked\0"
    "on_btnSpeed_top_clicked\0on_btnWriteProg_clicked\0"
    "on_btnCompProg_clicked\0"
    "on_comboBox_currentTextChanged\0"
    "on_btnDataAdd_clicked\0on_btnSendPoints_clicked\0"
    "on_tabJPointList_1_itemClicked\0"
    "QTableWidgetItem*\0item\0"
    "on_tabWPointList_1_itemClicked\0"
    "on_tabJPointList_2_itemClicked\0"
    "on_tabJPointList_3_itemClicked\0"
    "on_tabJPointList_4_itemClicked\0"
    "on_tabWPointList_2_itemClicked\0"
    "on_tabWPointList_3_itemClicked\0"
    "on_tabWPointList_4_itemClicked\0"
    "on_chbDIgr1_stateChanged\0"
    "on_chbDIgr2_stateChanged\0"
    "on_chbDIgr3_stateChanged\0"
    "on_chbDIgr4_stateChanged\0"
    "on_chbDIgr5_stateChanged\0"
    "on_chbDIgr6_stateChanged\0"
    "on_chbDIgr7_stateChanged\0"
    "on_chbDIgr8_stateChanged\0"
    "on_chbDIgr9_stateChanged\0"
    "on_chbDIgr10_stateChanged\0"
    "on_btnDataDel_clicked\0on_btnOpenPts_clicked\0"
    "on_btnSaveIP_clicked\0on_cbEnableDO_stateChanged\0"
    "on_chbDOgr1_stateChanged\0"
    "on_chbDOgr2_stateChanged\0"
    "on_chbDOgr3_stateChanged\0"
    "on_chbDOgr4_stateChanged\0"
    "on_chbDOgr5_stateChanged\0"
    "on_chbDOgr6_stateChanged\0"
    "on_chbDOgr7_stateChanged\0"
    "on_chbDOgr8_stateChanged\0"
    "on_chbDOgr9_stateChanged\0"
    "on_chbDOgr10_stateChanged\0on_btnDO1_toggled\0"
    "checked\0on_btnDO2_toggled\0on_btnDO3_toggled\0"
    "on_btnDO4_toggled\0on_btnDO5_toggled\0"
    "on_btnDO6_toggled\0on_btnDO7_toggled\0"
    "on_btnDO8_toggled\0on_combSeclvl_currentTextChanged\0"
    "on_btnOkpass_clicked\0on_btnRunprg_clicked\0"
    "on_btnPauseprg_clicked\0on_btnStopprg_clicked\0"
    "on_btnRBMode_toggled\0on_btnRBCLock_toggled\0"
    "on_btnRBServo_toggled\0on_btnSimRB_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     101,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  519,    2, 0x0a /* Public */,
       3,    0,  520,    2, 0x0a /* Public */,
       4,    0,  521,    2, 0x0a /* Public */,
       5,    0,  522,    2, 0x0a /* Public */,
       6,    0,  523,    2, 0x0a /* Public */,
       7,    1,  524,    2, 0x0a /* Public */,
      10,    1,  527,    2, 0x0a /* Public */,
      11,    1,  530,    2, 0x0a /* Public */,
      12,    1,  533,    2, 0x0a /* Public */,
      13,    1,  536,    2, 0x0a /* Public */,
      14,    0,  539,    2, 0x0a /* Public */,
      15,    0,  540,    2, 0x0a /* Public */,
      16,    1,  541,    2, 0x0a /* Public */,
      18,    1,  544,    2, 0x0a /* Public */,
      20,    0,  547,    2, 0x0a /* Public */,
      21,    0,  548,    2, 0x08 /* Private */,
      22,    0,  549,    2, 0x08 /* Private */,
      23,    0,  550,    2, 0x08 /* Private */,
      24,    0,  551,    2, 0x08 /* Private */,
      25,    0,  552,    2, 0x08 /* Private */,
      26,    0,  553,    2, 0x08 /* Private */,
      27,    0,  554,    2, 0x08 /* Private */,
      28,    0,  555,    2, 0x08 /* Private */,
      29,    0,  556,    2, 0x08 /* Private */,
      30,    0,  557,    2, 0x08 /* Private */,
      31,    0,  558,    2, 0x08 /* Private */,
      32,    0,  559,    2, 0x08 /* Private */,
      33,    0,  560,    2, 0x08 /* Private */,
      34,    0,  561,    2, 0x08 /* Private */,
      35,    0,  562,    2, 0x08 /* Private */,
      36,    0,  563,    2, 0x08 /* Private */,
      37,    0,  564,    2, 0x08 /* Private */,
      38,    0,  565,    2, 0x08 /* Private */,
      39,    0,  566,    2, 0x08 /* Private */,
      40,    0,  567,    2, 0x08 /* Private */,
      41,    0,  568,    2, 0x08 /* Private */,
      42,    0,  569,    2, 0x08 /* Private */,
      43,    0,  570,    2, 0x08 /* Private */,
      44,    0,  571,    2, 0x08 /* Private */,
      45,    0,  572,    2, 0x08 /* Private */,
      46,    0,  573,    2, 0x08 /* Private */,
      47,    1,  574,    2, 0x08 /* Private */,
      49,    0,  577,    2, 0x08 /* Private */,
      50,    0,  578,    2, 0x08 /* Private */,
      51,    0,  579,    2, 0x08 /* Private */,
      52,    0,  580,    2, 0x08 /* Private */,
      53,    0,  581,    2, 0x08 /* Private */,
      54,    0,  582,    2, 0x08 /* Private */,
      55,    0,  583,    2, 0x08 /* Private */,
      56,    1,  584,    2, 0x08 /* Private */,
      57,    0,  587,    2, 0x08 /* Private */,
      58,    0,  588,    2, 0x08 /* Private */,
      59,    1,  589,    2, 0x08 /* Private */,
      62,    1,  592,    2, 0x08 /* Private */,
      63,    1,  595,    2, 0x08 /* Private */,
      64,    1,  598,    2, 0x08 /* Private */,
      65,    1,  601,    2, 0x08 /* Private */,
      66,    1,  604,    2, 0x08 /* Private */,
      67,    1,  607,    2, 0x08 /* Private */,
      68,    1,  610,    2, 0x08 /* Private */,
      69,    1,  613,    2, 0x08 /* Private */,
      70,    1,  616,    2, 0x08 /* Private */,
      71,    1,  619,    2, 0x08 /* Private */,
      72,    1,  622,    2, 0x08 /* Private */,
      73,    1,  625,    2, 0x08 /* Private */,
      74,    1,  628,    2, 0x08 /* Private */,
      75,    1,  631,    2, 0x08 /* Private */,
      76,    1,  634,    2, 0x08 /* Private */,
      77,    1,  637,    2, 0x08 /* Private */,
      78,    1,  640,    2, 0x08 /* Private */,
      79,    0,  643,    2, 0x08 /* Private */,
      80,    0,  644,    2, 0x08 /* Private */,
      81,    0,  645,    2, 0x08 /* Private */,
      82,    1,  646,    2, 0x08 /* Private */,
      83,    1,  649,    2, 0x08 /* Private */,
      84,    1,  652,    2, 0x08 /* Private */,
      85,    1,  655,    2, 0x08 /* Private */,
      86,    1,  658,    2, 0x08 /* Private */,
      87,    1,  661,    2, 0x08 /* Private */,
      88,    1,  664,    2, 0x08 /* Private */,
      89,    1,  667,    2, 0x08 /* Private */,
      90,    1,  670,    2, 0x08 /* Private */,
      91,    1,  673,    2, 0x08 /* Private */,
      92,    1,  676,    2, 0x08 /* Private */,
      93,    1,  679,    2, 0x08 /* Private */,
      95,    1,  682,    2, 0x08 /* Private */,
      96,    1,  685,    2, 0x08 /* Private */,
      97,    1,  688,    2, 0x08 /* Private */,
      98,    1,  691,    2, 0x08 /* Private */,
      99,    1,  694,    2, 0x08 /* Private */,
     100,    1,  697,    2, 0x08 /* Private */,
     101,    1,  700,    2, 0x08 /* Private */,
     102,    1,  703,    2, 0x08 /* Private */,
     103,    0,  706,    2, 0x08 /* Private */,
     104,    0,  707,    2, 0x08 /* Private */,
     105,    0,  708,    2, 0x08 /* Private */,
     106,    0,  709,    2, 0x08 /* Private */,
     107,    1,  710,    2, 0x08 /* Private */,
     108,    1,  713,    2, 0x08 /* Private */,
     109,    1,  716,    2, 0x08 /* Private */,
     110,    0,  719,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, 0x80000000 | 60,   61,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void, QMetaType::Bool,   94,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateTimerTick(); break;
        case 1: _t->IOAlarmTick(); break;
        case 2: _t->Clock(); break;
        case 3: _t->ServerTimeout(); break;
        case 4: _t->JogRBTimer(); break;
        case 5: _t->ReadData((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 6: _t->Alarm((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 7: _t->ReadDeltaData((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 8: _t->ReadDI((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 9: _t->ReadDO((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 10: _t->DisplayDI(); break;
        case 11: _t->DisplayDO(); break;
        case 12: _t->JogProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->SetSttbar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->CheckCMDAck(); break;
        case 15: _t->on_btnStart_clicked(); break;
        case 16: _t->on_btnStop_clicked(); break;
        case 17: _t->on_btnJ1_neg_pressed(); break;
        case 18: _t->on_btnJ1_neg_released(); break;
        case 19: _t->on_btnJ1_pos_pressed(); break;
        case 20: _t->on_btnJ1_pos_released(); break;
        case 21: _t->on_btnJ2_neg_pressed(); break;
        case 22: _t->on_btnJ2_neg_released(); break;
        case 23: _t->on_btnJ2_pos_pressed(); break;
        case 24: _t->on_btnJ2_pos_released(); break;
        case 25: _t->on_btnJ3_neg_pressed(); break;
        case 26: _t->on_btnJ3_neg_released(); break;
        case 27: _t->on_btnJ3_pos_pressed(); break;
        case 28: _t->on_btnJ3_pos_released(); break;
        case 29: _t->on_btnJ4_neg_pressed(); break;
        case 30: _t->on_btnJ4_neg_released(); break;
        case 31: _t->on_btnJ4_pos_pressed(); break;
        case 32: _t->on_btnJ4_pos_released(); break;
        case 33: _t->on_btnJ5_neg_pressed(); break;
        case 34: _t->on_btnJ5_neg_released(); break;
        case 35: _t->on_btnJ5_pos_pressed(); break;
        case 36: _t->on_btnJ5_pos_released(); break;
        case 37: _t->on_btnJ6_neg_pressed(); break;
        case 38: _t->on_btnJ6_neg_released(); break;
        case 39: _t->on_btnJ6_pos_pressed(); break;
        case 40: _t->on_btnJ6_pos_released(); break;
        case 41: _t->on_chbCoords_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->on_btnSendProg_clicked(); break;
        case 43: _t->on_btnSpeed_low_clicked(); break;
        case 44: _t->on_btnSpeed_med_clicked(); break;
        case 45: _t->on_btnSpeed_high_clicked(); break;
        case 46: _t->on_btnSpeed_top_clicked(); break;
        case 47: _t->on_btnWriteProg_clicked(); break;
        case 48: _t->on_btnCompProg_clicked(); break;
        case 49: _t->on_comboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 50: _t->on_btnDataAdd_clicked(); break;
        case 51: _t->on_btnSendPoints_clicked(); break;
        case 52: _t->on_tabJPointList_1_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 53: _t->on_tabWPointList_1_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 54: _t->on_tabJPointList_2_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 55: _t->on_tabJPointList_3_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 56: _t->on_tabJPointList_4_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 57: _t->on_tabWPointList_2_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 58: _t->on_tabWPointList_3_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 59: _t->on_tabWPointList_4_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 60: _t->on_chbDIgr1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 61: _t->on_chbDIgr2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: _t->on_chbDIgr3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->on_chbDIgr4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->on_chbDIgr5_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 65: _t->on_chbDIgr6_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->on_chbDIgr7_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->on_chbDIgr8_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 68: _t->on_chbDIgr9_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 69: _t->on_chbDIgr10_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->on_btnDataDel_clicked(); break;
        case 71: _t->on_btnOpenPts_clicked(); break;
        case 72: _t->on_btnSaveIP_clicked(); break;
        case 73: _t->on_cbEnableDO_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 74: _t->on_chbDOgr1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 75: _t->on_chbDOgr2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->on_chbDOgr3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->on_chbDOgr4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->on_chbDOgr5_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->on_chbDOgr6_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 80: _t->on_chbDOgr7_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 81: _t->on_chbDOgr8_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 82: _t->on_chbDOgr9_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 83: _t->on_chbDOgr10_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 84: _t->on_btnDO1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 85: _t->on_btnDO2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 86: _t->on_btnDO3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 87: _t->on_btnDO4_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 88: _t->on_btnDO5_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 89: _t->on_btnDO6_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 90: _t->on_btnDO7_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 91: _t->on_btnDO8_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 92: _t->on_combSeclvl_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 93: _t->on_btnOkpass_clicked(); break;
        case 94: _t->on_btnRunprg_clicked(); break;
        case 95: _t->on_btnPauseprg_clicked(); break;
        case 96: _t->on_btnStopprg_clicked(); break;
        case 97: _t->on_btnRBMode_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 98: _t->on_btnRBCLock_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 99: _t->on_btnRBServo_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 100: _t->on_btnSimRB_clicked(); break;
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
        if (_id < 101)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 101;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 101)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 101;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
