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
    QByteArrayData data[154];
    char stringdata0[3076];
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
QT_MOC_LITERAL(3, 28, 5), // "Clock"
QT_MOC_LITERAL(4, 34, 13), // "ServerTimeout"
QT_MOC_LITERAL(5, 48, 8), // "ReadData"
QT_MOC_LITERAL(6, 57, 10), // "UA_Client*"
QT_MOC_LITERAL(7, 68, 6), // "client"
QT_MOC_LITERAL(8, 75, 5), // "Alarm"
QT_MOC_LITERAL(9, 81, 13), // "ReadDeltaData"
QT_MOC_LITERAL(10, 95, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(11, 115, 18), // "on_btnStop_clicked"
QT_MOC_LITERAL(12, 134, 20), // "on_btnJ1_neg_pressed"
QT_MOC_LITERAL(13, 155, 21), // "on_btnJ1_neg_released"
QT_MOC_LITERAL(14, 177, 20), // "on_btnJ1_pos_pressed"
QT_MOC_LITERAL(15, 198, 21), // "on_btnJ1_pos_released"
QT_MOC_LITERAL(16, 220, 20), // "on_btnJ2_neg_pressed"
QT_MOC_LITERAL(17, 241, 21), // "on_btnJ2_neg_released"
QT_MOC_LITERAL(18, 263, 20), // "on_btnJ2_pos_pressed"
QT_MOC_LITERAL(19, 284, 21), // "on_btnJ2_pos_released"
QT_MOC_LITERAL(20, 306, 20), // "on_btnJ3_neg_pressed"
QT_MOC_LITERAL(21, 327, 21), // "on_btnJ3_neg_released"
QT_MOC_LITERAL(22, 349, 20), // "on_btnJ3_pos_pressed"
QT_MOC_LITERAL(23, 370, 21), // "on_btnJ3_pos_released"
QT_MOC_LITERAL(24, 392, 20), // "on_btnJ4_neg_pressed"
QT_MOC_LITERAL(25, 413, 21), // "on_btnJ4_neg_released"
QT_MOC_LITERAL(26, 435, 20), // "on_btnJ4_pos_pressed"
QT_MOC_LITERAL(27, 456, 21), // "on_btnJ4_pos_released"
QT_MOC_LITERAL(28, 478, 20), // "on_btnJ5_neg_pressed"
QT_MOC_LITERAL(29, 499, 21), // "on_btnJ5_neg_released"
QT_MOC_LITERAL(30, 521, 20), // "on_btnJ5_pos_pressed"
QT_MOC_LITERAL(31, 542, 21), // "on_btnJ5_pos_released"
QT_MOC_LITERAL(32, 564, 20), // "on_btnJ6_neg_pressed"
QT_MOC_LITERAL(33, 585, 21), // "on_btnJ6_neg_released"
QT_MOC_LITERAL(34, 607, 20), // "on_btnJ6_pos_pressed"
QT_MOC_LITERAL(35, 628, 21), // "on_btnJ6_pos_released"
QT_MOC_LITERAL(36, 650, 18), // "on_btnSVON_clicked"
QT_MOC_LITERAL(37, 669, 19), // "on_btnSVOFF_clicked"
QT_MOC_LITERAL(38, 689, 31), // "on_chbCoords_currentTextChanged"
QT_MOC_LITERAL(39, 721, 4), // "arg1"
QT_MOC_LITERAL(40, 726, 22), // "on_btnSendProg_clicked"
QT_MOC_LITERAL(41, 749, 23), // "on_btnSpeed_low_clicked"
QT_MOC_LITERAL(42, 773, 23), // "on_btnSpeed_med_clicked"
QT_MOC_LITERAL(43, 797, 24), // "on_btnSpeed_high_clicked"
QT_MOC_LITERAL(44, 822, 23), // "on_btnSpeed_top_clicked"
QT_MOC_LITERAL(45, 846, 23), // "on_btnWriteProg_clicked"
QT_MOC_LITERAL(46, 870, 22), // "on_btnCompProg_clicked"
QT_MOC_LITERAL(47, 893, 30), // "on_comboBox_currentTextChanged"
QT_MOC_LITERAL(48, 924, 21), // "on_btnDataAdd_clicked"
QT_MOC_LITERAL(49, 946, 24), // "on_btnSendPoints_clicked"
QT_MOC_LITERAL(50, 971, 30), // "on_tabJPointList_1_itemClicked"
QT_MOC_LITERAL(51, 1002, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(52, 1020, 4), // "item"
QT_MOC_LITERAL(53, 1025, 30), // "on_tabWPointList_1_itemClicked"
QT_MOC_LITERAL(54, 1056, 30), // "on_tabJPointList_2_itemClicked"
QT_MOC_LITERAL(55, 1087, 30), // "on_tabJPointList_3_itemClicked"
QT_MOC_LITERAL(56, 1118, 30), // "on_tabJPointList_4_itemClicked"
QT_MOC_LITERAL(57, 1149, 30), // "on_tabWPointList_2_itemClicked"
QT_MOC_LITERAL(58, 1180, 30), // "on_tabWPointList_3_itemClicked"
QT_MOC_LITERAL(59, 1211, 30), // "on_tabWPointList_4_itemClicked"
QT_MOC_LITERAL(60, 1242, 17), // "on_btnDI7_toggled"
QT_MOC_LITERAL(61, 1260, 7), // "checked"
QT_MOC_LITERAL(62, 1268, 17), // "on_btnDI6_toggled"
QT_MOC_LITERAL(63, 1286, 17), // "on_btnDI5_toggled"
QT_MOC_LITERAL(64, 1304, 17), // "on_btnDI4_toggled"
QT_MOC_LITERAL(65, 1322, 17), // "on_btnDI3_toggled"
QT_MOC_LITERAL(66, 1340, 17), // "on_btnDI2_toggled"
QT_MOC_LITERAL(67, 1358, 17), // "on_btnDI1_toggled"
QT_MOC_LITERAL(68, 1376, 17), // "on_btnDI0_toggled"
QT_MOC_LITERAL(69, 1394, 18), // "on_btnDI15_toggled"
QT_MOC_LITERAL(70, 1413, 18), // "on_btnDI14_toggled"
QT_MOC_LITERAL(71, 1432, 18), // "on_btnDI13_toggled"
QT_MOC_LITERAL(72, 1451, 18), // "on_btnDI12_toggled"
QT_MOC_LITERAL(73, 1470, 18), // "on_btnDI11_toggled"
QT_MOC_LITERAL(74, 1489, 18), // "on_btnDI10_toggled"
QT_MOC_LITERAL(75, 1508, 17), // "on_btnDI9_toggled"
QT_MOC_LITERAL(76, 1526, 17), // "on_btnDI8_toggled"
QT_MOC_LITERAL(77, 1544, 18), // "on_btnDI23_toggled"
QT_MOC_LITERAL(78, 1563, 18), // "on_btnDI22_toggled"
QT_MOC_LITERAL(79, 1582, 18), // "on_btnDI21_toggled"
QT_MOC_LITERAL(80, 1601, 18), // "on_btnDI20_toggled"
QT_MOC_LITERAL(81, 1620, 18), // "on_btnDI19_toggled"
QT_MOC_LITERAL(82, 1639, 18), // "on_btnDI18_toggled"
QT_MOC_LITERAL(83, 1658, 18), // "on_btnDI17_toggled"
QT_MOC_LITERAL(84, 1677, 18), // "on_btnDI16_toggled"
QT_MOC_LITERAL(85, 1696, 18), // "on_btnDI31_toggled"
QT_MOC_LITERAL(86, 1715, 18), // "on_btnDI30_toggled"
QT_MOC_LITERAL(87, 1734, 18), // "on_btnDI29_toggled"
QT_MOC_LITERAL(88, 1753, 18), // "on_btnDI28_toggled"
QT_MOC_LITERAL(89, 1772, 18), // "on_btnDI27_toggled"
QT_MOC_LITERAL(90, 1791, 18), // "on_btnDI26_toggled"
QT_MOC_LITERAL(91, 1810, 18), // "on_btnDI25_toggled"
QT_MOC_LITERAL(92, 1829, 18), // "on_btnDI24_toggled"
QT_MOC_LITERAL(93, 1848, 18), // "on_btnDI39_toggled"
QT_MOC_LITERAL(94, 1867, 18), // "on_btnDI38_toggled"
QT_MOC_LITERAL(95, 1886, 18), // "on_btnDI37_toggled"
QT_MOC_LITERAL(96, 1905, 18), // "on_btnDI36_toggled"
QT_MOC_LITERAL(97, 1924, 18), // "on_btnDI35_toggled"
QT_MOC_LITERAL(98, 1943, 18), // "on_btnDI34_toggled"
QT_MOC_LITERAL(99, 1962, 18), // "on_btnDI33_toggled"
QT_MOC_LITERAL(100, 1981, 18), // "on_btnDI32_toggled"
QT_MOC_LITERAL(101, 2000, 18), // "on_btnDI47_toggled"
QT_MOC_LITERAL(102, 2019, 18), // "on_btnDI46_toggled"
QT_MOC_LITERAL(103, 2038, 18), // "on_btnDI45_toggled"
QT_MOC_LITERAL(104, 2057, 18), // "on_btnDI44_toggled"
QT_MOC_LITERAL(105, 2076, 18), // "on_btnDI43_toggled"
QT_MOC_LITERAL(106, 2095, 18), // "on_btnDI42_toggled"
QT_MOC_LITERAL(107, 2114, 18), // "on_btnDI41_toggled"
QT_MOC_LITERAL(108, 2133, 18), // "on_btnDI40_toggled"
QT_MOC_LITERAL(109, 2152, 18), // "on_btnDI55_toggled"
QT_MOC_LITERAL(110, 2171, 18), // "on_btnDI54_toggled"
QT_MOC_LITERAL(111, 2190, 18), // "on_btnDI53_toggled"
QT_MOC_LITERAL(112, 2209, 18), // "on_btnDI52_toggled"
QT_MOC_LITERAL(113, 2228, 18), // "on_btnDI51_toggled"
QT_MOC_LITERAL(114, 2247, 18), // "on_btnDI50_toggled"
QT_MOC_LITERAL(115, 2266, 18), // "on_btnDI49_toggled"
QT_MOC_LITERAL(116, 2285, 18), // "on_btnDI48_toggled"
QT_MOC_LITERAL(117, 2304, 18), // "on_btnDI63_toggled"
QT_MOC_LITERAL(118, 2323, 18), // "on_btnDI62_toggled"
QT_MOC_LITERAL(119, 2342, 18), // "on_btnDI61_toggled"
QT_MOC_LITERAL(120, 2361, 18), // "on_btnDI60_toggled"
QT_MOC_LITERAL(121, 2380, 18), // "on_btnDI59_toggled"
QT_MOC_LITERAL(122, 2399, 18), // "on_btnDI58_toggled"
QT_MOC_LITERAL(123, 2418, 18), // "on_btnDI57_toggled"
QT_MOC_LITERAL(124, 2437, 18), // "on_btnDI56_toggled"
QT_MOC_LITERAL(125, 2456, 18), // "on_btnDI71_toggled"
QT_MOC_LITERAL(126, 2475, 18), // "on_btnDI70_toggled"
QT_MOC_LITERAL(127, 2494, 18), // "on_btnDI69_toggled"
QT_MOC_LITERAL(128, 2513, 18), // "on_btnDI68_toggled"
QT_MOC_LITERAL(129, 2532, 18), // "on_btnDI67_toggled"
QT_MOC_LITERAL(130, 2551, 18), // "on_btnDI66_toggled"
QT_MOC_LITERAL(131, 2570, 18), // "on_btnDI65_toggled"
QT_MOC_LITERAL(132, 2589, 18), // "on_btnDI64_toggled"
QT_MOC_LITERAL(133, 2608, 18), // "on_btnDI79_toggled"
QT_MOC_LITERAL(134, 2627, 18), // "on_btnDI78_toggled"
QT_MOC_LITERAL(135, 2646, 18), // "on_btnDI77_toggled"
QT_MOC_LITERAL(136, 2665, 18), // "on_btnDI76_toggled"
QT_MOC_LITERAL(137, 2684, 18), // "on_btnDI75_toggled"
QT_MOC_LITERAL(138, 2703, 18), // "on_btnDI74_toggled"
QT_MOC_LITERAL(139, 2722, 18), // "on_btnDI73_toggled"
QT_MOC_LITERAL(140, 2741, 18), // "on_btnDI72_toggled"
QT_MOC_LITERAL(141, 2760, 24), // "on_chbDIgr1_stateChanged"
QT_MOC_LITERAL(142, 2785, 24), // "on_chbDIgr2_stateChanged"
QT_MOC_LITERAL(143, 2810, 24), // "on_chbDIgr3_stateChanged"
QT_MOC_LITERAL(144, 2835, 24), // "on_chbDIgr4_stateChanged"
QT_MOC_LITERAL(145, 2860, 24), // "on_chbDIgr5_stateChanged"
QT_MOC_LITERAL(146, 2885, 24), // "on_chbDIgr6_stateChanged"
QT_MOC_LITERAL(147, 2910, 24), // "on_chbDIgr7_stateChanged"
QT_MOC_LITERAL(148, 2935, 24), // "on_chbDIgr8_stateChanged"
QT_MOC_LITERAL(149, 2960, 24), // "on_chbDIgr9_stateChanged"
QT_MOC_LITERAL(150, 2985, 25), // "on_chbDIgr10_stateChanged"
QT_MOC_LITERAL(151, 3011, 21), // "on_btnDataDel_clicked"
QT_MOC_LITERAL(152, 3033, 21), // "on_btnOpenPts_clicked"
QT_MOC_LITERAL(153, 3055, 20) // "on_btnSaveIP_clicked"

    },
    "MainWindow\0UpdateTimerTick\0\0Clock\0"
    "ServerTimeout\0ReadData\0UA_Client*\0"
    "client\0Alarm\0ReadDeltaData\0"
    "on_btnStart_clicked\0on_btnStop_clicked\0"
    "on_btnJ1_neg_pressed\0on_btnJ1_neg_released\0"
    "on_btnJ1_pos_pressed\0on_btnJ1_pos_released\0"
    "on_btnJ2_neg_pressed\0on_btnJ2_neg_released\0"
    "on_btnJ2_pos_pressed\0on_btnJ2_pos_released\0"
    "on_btnJ3_neg_pressed\0on_btnJ3_neg_released\0"
    "on_btnJ3_pos_pressed\0on_btnJ3_pos_released\0"
    "on_btnJ4_neg_pressed\0on_btnJ4_neg_released\0"
    "on_btnJ4_pos_pressed\0on_btnJ4_pos_released\0"
    "on_btnJ5_neg_pressed\0on_btnJ5_neg_released\0"
    "on_btnJ5_pos_pressed\0on_btnJ5_pos_released\0"
    "on_btnJ6_neg_pressed\0on_btnJ6_neg_released\0"
    "on_btnJ6_pos_pressed\0on_btnJ6_pos_released\0"
    "on_btnSVON_clicked\0on_btnSVOFF_clicked\0"
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
    "on_btnDI7_toggled\0checked\0on_btnDI6_toggled\0"
    "on_btnDI5_toggled\0on_btnDI4_toggled\0"
    "on_btnDI3_toggled\0on_btnDI2_toggled\0"
    "on_btnDI1_toggled\0on_btnDI0_toggled\0"
    "on_btnDI15_toggled\0on_btnDI14_toggled\0"
    "on_btnDI13_toggled\0on_btnDI12_toggled\0"
    "on_btnDI11_toggled\0on_btnDI10_toggled\0"
    "on_btnDI9_toggled\0on_btnDI8_toggled\0"
    "on_btnDI23_toggled\0on_btnDI22_toggled\0"
    "on_btnDI21_toggled\0on_btnDI20_toggled\0"
    "on_btnDI19_toggled\0on_btnDI18_toggled\0"
    "on_btnDI17_toggled\0on_btnDI16_toggled\0"
    "on_btnDI31_toggled\0on_btnDI30_toggled\0"
    "on_btnDI29_toggled\0on_btnDI28_toggled\0"
    "on_btnDI27_toggled\0on_btnDI26_toggled\0"
    "on_btnDI25_toggled\0on_btnDI24_toggled\0"
    "on_btnDI39_toggled\0on_btnDI38_toggled\0"
    "on_btnDI37_toggled\0on_btnDI36_toggled\0"
    "on_btnDI35_toggled\0on_btnDI34_toggled\0"
    "on_btnDI33_toggled\0on_btnDI32_toggled\0"
    "on_btnDI47_toggled\0on_btnDI46_toggled\0"
    "on_btnDI45_toggled\0on_btnDI44_toggled\0"
    "on_btnDI43_toggled\0on_btnDI42_toggled\0"
    "on_btnDI41_toggled\0on_btnDI40_toggled\0"
    "on_btnDI55_toggled\0on_btnDI54_toggled\0"
    "on_btnDI53_toggled\0on_btnDI52_toggled\0"
    "on_btnDI51_toggled\0on_btnDI50_toggled\0"
    "on_btnDI49_toggled\0on_btnDI48_toggled\0"
    "on_btnDI63_toggled\0on_btnDI62_toggled\0"
    "on_btnDI61_toggled\0on_btnDI60_toggled\0"
    "on_btnDI59_toggled\0on_btnDI58_toggled\0"
    "on_btnDI57_toggled\0on_btnDI56_toggled\0"
    "on_btnDI71_toggled\0on_btnDI70_toggled\0"
    "on_btnDI69_toggled\0on_btnDI68_toggled\0"
    "on_btnDI67_toggled\0on_btnDI66_toggled\0"
    "on_btnDI65_toggled\0on_btnDI64_toggled\0"
    "on_btnDI79_toggled\0on_btnDI78_toggled\0"
    "on_btnDI77_toggled\0on_btnDI76_toggled\0"
    "on_btnDI75_toggled\0on_btnDI74_toggled\0"
    "on_btnDI73_toggled\0on_btnDI72_toggled\0"
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
    "on_btnSaveIP_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     146,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  744,    2, 0x0a /* Public */,
       3,    0,  745,    2, 0x0a /* Public */,
       4,    0,  746,    2, 0x0a /* Public */,
       5,    1,  747,    2, 0x0a /* Public */,
       8,    1,  750,    2, 0x0a /* Public */,
       9,    1,  753,    2, 0x0a /* Public */,
      10,    0,  756,    2, 0x08 /* Private */,
      11,    0,  757,    2, 0x08 /* Private */,
      12,    0,  758,    2, 0x08 /* Private */,
      13,    0,  759,    2, 0x08 /* Private */,
      14,    0,  760,    2, 0x08 /* Private */,
      15,    0,  761,    2, 0x08 /* Private */,
      16,    0,  762,    2, 0x08 /* Private */,
      17,    0,  763,    2, 0x08 /* Private */,
      18,    0,  764,    2, 0x08 /* Private */,
      19,    0,  765,    2, 0x08 /* Private */,
      20,    0,  766,    2, 0x08 /* Private */,
      21,    0,  767,    2, 0x08 /* Private */,
      22,    0,  768,    2, 0x08 /* Private */,
      23,    0,  769,    2, 0x08 /* Private */,
      24,    0,  770,    2, 0x08 /* Private */,
      25,    0,  771,    2, 0x08 /* Private */,
      26,    0,  772,    2, 0x08 /* Private */,
      27,    0,  773,    2, 0x08 /* Private */,
      28,    0,  774,    2, 0x08 /* Private */,
      29,    0,  775,    2, 0x08 /* Private */,
      30,    0,  776,    2, 0x08 /* Private */,
      31,    0,  777,    2, 0x08 /* Private */,
      32,    0,  778,    2, 0x08 /* Private */,
      33,    0,  779,    2, 0x08 /* Private */,
      34,    0,  780,    2, 0x08 /* Private */,
      35,    0,  781,    2, 0x08 /* Private */,
      36,    0,  782,    2, 0x08 /* Private */,
      37,    0,  783,    2, 0x08 /* Private */,
      38,    1,  784,    2, 0x08 /* Private */,
      40,    0,  787,    2, 0x08 /* Private */,
      41,    0,  788,    2, 0x08 /* Private */,
      42,    0,  789,    2, 0x08 /* Private */,
      43,    0,  790,    2, 0x08 /* Private */,
      44,    0,  791,    2, 0x08 /* Private */,
      45,    0,  792,    2, 0x08 /* Private */,
      46,    0,  793,    2, 0x08 /* Private */,
      47,    1,  794,    2, 0x08 /* Private */,
      48,    0,  797,    2, 0x08 /* Private */,
      49,    0,  798,    2, 0x08 /* Private */,
      50,    1,  799,    2, 0x08 /* Private */,
      53,    1,  802,    2, 0x08 /* Private */,
      54,    1,  805,    2, 0x08 /* Private */,
      55,    1,  808,    2, 0x08 /* Private */,
      56,    1,  811,    2, 0x08 /* Private */,
      57,    1,  814,    2, 0x08 /* Private */,
      58,    1,  817,    2, 0x08 /* Private */,
      59,    1,  820,    2, 0x08 /* Private */,
      60,    1,  823,    2, 0x08 /* Private */,
      62,    1,  826,    2, 0x08 /* Private */,
      63,    1,  829,    2, 0x08 /* Private */,
      64,    1,  832,    2, 0x08 /* Private */,
      65,    1,  835,    2, 0x08 /* Private */,
      66,    1,  838,    2, 0x08 /* Private */,
      67,    1,  841,    2, 0x08 /* Private */,
      68,    1,  844,    2, 0x08 /* Private */,
      69,    1,  847,    2, 0x08 /* Private */,
      70,    1,  850,    2, 0x08 /* Private */,
      71,    1,  853,    2, 0x08 /* Private */,
      72,    1,  856,    2, 0x08 /* Private */,
      73,    1,  859,    2, 0x08 /* Private */,
      74,    1,  862,    2, 0x08 /* Private */,
      75,    1,  865,    2, 0x08 /* Private */,
      76,    1,  868,    2, 0x08 /* Private */,
      77,    1,  871,    2, 0x08 /* Private */,
      78,    1,  874,    2, 0x08 /* Private */,
      79,    1,  877,    2, 0x08 /* Private */,
      80,    1,  880,    2, 0x08 /* Private */,
      81,    1,  883,    2, 0x08 /* Private */,
      82,    1,  886,    2, 0x08 /* Private */,
      83,    1,  889,    2, 0x08 /* Private */,
      84,    1,  892,    2, 0x08 /* Private */,
      85,    1,  895,    2, 0x08 /* Private */,
      86,    1,  898,    2, 0x08 /* Private */,
      87,    1,  901,    2, 0x08 /* Private */,
      88,    1,  904,    2, 0x08 /* Private */,
      89,    1,  907,    2, 0x08 /* Private */,
      90,    1,  910,    2, 0x08 /* Private */,
      91,    1,  913,    2, 0x08 /* Private */,
      92,    1,  916,    2, 0x08 /* Private */,
      93,    1,  919,    2, 0x08 /* Private */,
      94,    1,  922,    2, 0x08 /* Private */,
      95,    1,  925,    2, 0x08 /* Private */,
      96,    1,  928,    2, 0x08 /* Private */,
      97,    1,  931,    2, 0x08 /* Private */,
      98,    1,  934,    2, 0x08 /* Private */,
      99,    1,  937,    2, 0x08 /* Private */,
     100,    1,  940,    2, 0x08 /* Private */,
     101,    1,  943,    2, 0x08 /* Private */,
     102,    1,  946,    2, 0x08 /* Private */,
     103,    1,  949,    2, 0x08 /* Private */,
     104,    1,  952,    2, 0x08 /* Private */,
     105,    1,  955,    2, 0x08 /* Private */,
     106,    1,  958,    2, 0x08 /* Private */,
     107,    1,  961,    2, 0x08 /* Private */,
     108,    1,  964,    2, 0x08 /* Private */,
     109,    1,  967,    2, 0x08 /* Private */,
     110,    1,  970,    2, 0x08 /* Private */,
     111,    1,  973,    2, 0x08 /* Private */,
     112,    1,  976,    2, 0x08 /* Private */,
     113,    1,  979,    2, 0x08 /* Private */,
     114,    1,  982,    2, 0x08 /* Private */,
     115,    1,  985,    2, 0x08 /* Private */,
     116,    1,  988,    2, 0x08 /* Private */,
     117,    1,  991,    2, 0x08 /* Private */,
     118,    1,  994,    2, 0x08 /* Private */,
     119,    1,  997,    2, 0x08 /* Private */,
     120,    1, 1000,    2, 0x08 /* Private */,
     121,    1, 1003,    2, 0x08 /* Private */,
     122,    1, 1006,    2, 0x08 /* Private */,
     123,    1, 1009,    2, 0x08 /* Private */,
     124,    1, 1012,    2, 0x08 /* Private */,
     125,    1, 1015,    2, 0x08 /* Private */,
     126,    1, 1018,    2, 0x08 /* Private */,
     127,    1, 1021,    2, 0x08 /* Private */,
     128,    1, 1024,    2, 0x08 /* Private */,
     129,    1, 1027,    2, 0x08 /* Private */,
     130,    1, 1030,    2, 0x08 /* Private */,
     131,    1, 1033,    2, 0x08 /* Private */,
     132,    1, 1036,    2, 0x08 /* Private */,
     133,    1, 1039,    2, 0x08 /* Private */,
     134,    1, 1042,    2, 0x08 /* Private */,
     135,    1, 1045,    2, 0x08 /* Private */,
     136,    1, 1048,    2, 0x08 /* Private */,
     137,    1, 1051,    2, 0x08 /* Private */,
     138,    1, 1054,    2, 0x08 /* Private */,
     139,    1, 1057,    2, 0x08 /* Private */,
     140,    1, 1060,    2, 0x08 /* Private */,
     141,    1, 1063,    2, 0x08 /* Private */,
     142,    1, 1066,    2, 0x08 /* Private */,
     143,    1, 1069,    2, 0x08 /* Private */,
     144,    1, 1072,    2, 0x08 /* Private */,
     145,    1, 1075,    2, 0x08 /* Private */,
     146,    1, 1078,    2, 0x08 /* Private */,
     147,    1, 1081,    2, 0x08 /* Private */,
     148,    1, 1084,    2, 0x08 /* Private */,
     149,    1, 1087,    2, 0x08 /* Private */,
     150,    1, 1090,    2, 0x08 /* Private */,
     151,    0, 1093,    2, 0x08 /* Private */,
     152,    0, 1094,    2, 0x08 /* Private */,
     153,    0, 1095,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
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
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void,
    QMetaType::Void,
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
        case 1: _t->Clock(); break;
        case 2: _t->ServerTimeout(); break;
        case 3: _t->ReadData((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 4: _t->Alarm((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 5: _t->ReadDeltaData((*reinterpret_cast< UA_Client*(*)>(_a[1]))); break;
        case 6: _t->on_btnStart_clicked(); break;
        case 7: _t->on_btnStop_clicked(); break;
        case 8: _t->on_btnJ1_neg_pressed(); break;
        case 9: _t->on_btnJ1_neg_released(); break;
        case 10: _t->on_btnJ1_pos_pressed(); break;
        case 11: _t->on_btnJ1_pos_released(); break;
        case 12: _t->on_btnJ2_neg_pressed(); break;
        case 13: _t->on_btnJ2_neg_released(); break;
        case 14: _t->on_btnJ2_pos_pressed(); break;
        case 15: _t->on_btnJ2_pos_released(); break;
        case 16: _t->on_btnJ3_neg_pressed(); break;
        case 17: _t->on_btnJ3_neg_released(); break;
        case 18: _t->on_btnJ3_pos_pressed(); break;
        case 19: _t->on_btnJ3_pos_released(); break;
        case 20: _t->on_btnJ4_neg_pressed(); break;
        case 21: _t->on_btnJ4_neg_released(); break;
        case 22: _t->on_btnJ4_pos_pressed(); break;
        case 23: _t->on_btnJ4_pos_released(); break;
        case 24: _t->on_btnJ5_neg_pressed(); break;
        case 25: _t->on_btnJ5_neg_released(); break;
        case 26: _t->on_btnJ5_pos_pressed(); break;
        case 27: _t->on_btnJ5_pos_released(); break;
        case 28: _t->on_btnJ6_neg_pressed(); break;
        case 29: _t->on_btnJ6_neg_released(); break;
        case 30: _t->on_btnJ6_pos_pressed(); break;
        case 31: _t->on_btnJ6_pos_released(); break;
        case 32: _t->on_btnSVON_clicked(); break;
        case 33: _t->on_btnSVOFF_clicked(); break;
        case 34: _t->on_chbCoords_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: _t->on_btnSendProg_clicked(); break;
        case 36: _t->on_btnSpeed_low_clicked(); break;
        case 37: _t->on_btnSpeed_med_clicked(); break;
        case 38: _t->on_btnSpeed_high_clicked(); break;
        case 39: _t->on_btnSpeed_top_clicked(); break;
        case 40: _t->on_btnWriteProg_clicked(); break;
        case 41: _t->on_btnCompProg_clicked(); break;
        case 42: _t->on_comboBox_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 43: _t->on_btnDataAdd_clicked(); break;
        case 44: _t->on_btnSendPoints_clicked(); break;
        case 45: _t->on_tabJPointList_1_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 46: _t->on_tabWPointList_1_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 47: _t->on_tabJPointList_2_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 48: _t->on_tabJPointList_3_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 49: _t->on_tabJPointList_4_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 50: _t->on_tabWPointList_2_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 51: _t->on_tabWPointList_3_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 52: _t->on_tabWPointList_4_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 53: _t->on_btnDI7_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->on_btnDI6_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->on_btnDI5_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->on_btnDI4_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->on_btnDI3_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->on_btnDI2_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->on_btnDI1_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->on_btnDI0_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->on_btnDI15_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->on_btnDI14_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->on_btnDI13_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->on_btnDI12_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->on_btnDI11_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->on_btnDI10_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->on_btnDI9_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 68: _t->on_btnDI8_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 69: _t->on_btnDI23_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 70: _t->on_btnDI22_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 71: _t->on_btnDI21_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 72: _t->on_btnDI20_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 73: _t->on_btnDI19_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 74: _t->on_btnDI18_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 75: _t->on_btnDI17_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 76: _t->on_btnDI16_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 77: _t->on_btnDI31_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 78: _t->on_btnDI30_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 79: _t->on_btnDI29_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 80: _t->on_btnDI28_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 81: _t->on_btnDI27_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 82: _t->on_btnDI26_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 83: _t->on_btnDI25_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 84: _t->on_btnDI24_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 85: _t->on_btnDI39_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 86: _t->on_btnDI38_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 87: _t->on_btnDI37_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 88: _t->on_btnDI36_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 89: _t->on_btnDI35_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 90: _t->on_btnDI34_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 91: _t->on_btnDI33_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 92: _t->on_btnDI32_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 93: _t->on_btnDI47_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 94: _t->on_btnDI46_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 95: _t->on_btnDI45_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 96: _t->on_btnDI44_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 97: _t->on_btnDI43_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 98: _t->on_btnDI42_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 99: _t->on_btnDI41_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 100: _t->on_btnDI40_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 101: _t->on_btnDI55_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 102: _t->on_btnDI54_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 103: _t->on_btnDI53_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 104: _t->on_btnDI52_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 105: _t->on_btnDI51_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 106: _t->on_btnDI50_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 107: _t->on_btnDI49_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 108: _t->on_btnDI48_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 109: _t->on_btnDI63_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 110: _t->on_btnDI62_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 111: _t->on_btnDI61_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 112: _t->on_btnDI60_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 113: _t->on_btnDI59_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 114: _t->on_btnDI58_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 115: _t->on_btnDI57_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 116: _t->on_btnDI56_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 117: _t->on_btnDI71_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 118: _t->on_btnDI70_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 119: _t->on_btnDI69_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 120: _t->on_btnDI68_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 121: _t->on_btnDI67_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 122: _t->on_btnDI66_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 123: _t->on_btnDI65_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 124: _t->on_btnDI64_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 125: _t->on_btnDI79_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 126: _t->on_btnDI78_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 127: _t->on_btnDI77_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 128: _t->on_btnDI76_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 129: _t->on_btnDI75_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 130: _t->on_btnDI74_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 131: _t->on_btnDI73_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 132: _t->on_btnDI72_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 133: _t->on_chbDIgr1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 134: _t->on_chbDIgr2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 135: _t->on_chbDIgr3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 136: _t->on_chbDIgr4_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 137: _t->on_chbDIgr5_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 138: _t->on_chbDIgr6_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 139: _t->on_chbDIgr7_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 140: _t->on_chbDIgr8_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 141: _t->on_chbDIgr9_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 142: _t->on_chbDIgr10_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 143: _t->on_btnDataDel_clicked(); break;
        case 144: _t->on_btnOpenPts_clicked(); break;
        case 145: _t->on_btnSaveIP_clicked(); break;
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
        if (_id < 146)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 146;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 146)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 146;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
