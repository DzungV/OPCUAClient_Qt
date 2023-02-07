#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/types_generated.h>
#include <open62541/types.h>
#include <stdlib.h>
#include "QCodeEditor_Example.hpp"
#include <QTableWidget>
#include <QTableWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();






    void ClientConnect (int status);



public slots:
    void UpdateTimerTick();
    void Clock();
    void ServerTimeout();
    void ReadData(UA_Client *client);
    void Alarm(UA_Client *client);
    void ReadDeltaData(UA_Client *client);

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnJ1_neg_pressed();

    void on_btnJ1_neg_released();

    void on_btnJ1_pos_pressed();

    void on_btnJ1_pos_released();

    void on_btnJ2_neg_pressed();

    void on_btnJ2_neg_released();

    void on_btnJ2_pos_pressed();

    void on_btnJ2_pos_released();

    void on_btnJ3_neg_pressed();

    void on_btnJ3_neg_released();

    void on_btnJ3_pos_pressed();

    void on_btnJ3_pos_released();

    void on_btnJ4_neg_pressed();

    void on_btnJ4_neg_released();

    void on_btnJ4_pos_pressed();

    void on_btnJ4_pos_released();

    void on_btnJ5_neg_pressed();

    void on_btnJ5_neg_released();

    void on_btnJ5_pos_pressed();

    void on_btnJ5_pos_released();

    void on_btnJ6_neg_pressed();

    void on_btnJ6_neg_released();

    void on_btnJ6_pos_pressed();

    void on_btnJ6_pos_released();

    void on_btnSVON_clicked();

    void on_btnSVOFF_clicked();



    void on_chbCoords_currentTextChanged(const QString &arg1);

    void on_btnSendProg_clicked();

    void on_btnSpeed_low_clicked();

    void on_btnSpeed_med_clicked();

    void on_btnSpeed_high_clicked();

    void on_btnSpeed_top_clicked();

    void on_btnWriteProg_clicked();

    void on_btnCompProg_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_btnDataAdd_clicked();

    void on_btnSendPoints_clicked();

    void on_tabJPointList_1_itemClicked(QTableWidgetItem *item);

    void on_tabWPointList_1_itemClicked(QTableWidgetItem *item);

    void on_tabJPointList_2_itemClicked(QTableWidgetItem *item);

    void on_tabJPointList_3_itemClicked(QTableWidgetItem *item);

    void on_tabJPointList_4_itemClicked(QTableWidgetItem *item);

    void on_tabWPointList_2_itemClicked(QTableWidgetItem *item);

    void on_tabWPointList_3_itemClicked(QTableWidgetItem *item);

    void on_tabWPointList_4_itemClicked(QTableWidgetItem *item);

    void on_btnDI7_toggled(bool checked);

    void on_btnDI6_toggled(bool checked);

    void on_btnDI5_toggled(bool checked);

    void on_btnDI4_toggled(bool checked);

    void on_btnDI3_toggled(bool checked);

    void on_btnDI2_toggled(bool checked);

    void on_btnDI1_toggled(bool checked);

    void on_btnDI0_toggled(bool checked);

    void on_btnDI15_toggled(bool checked);

    void on_btnDI14_toggled(bool checked);

    void on_btnDI13_toggled(bool checked);

    void on_btnDI12_toggled(bool checked);

    void on_btnDI11_toggled(bool checked);

    void on_btnDI10_toggled(bool checked);

    void on_btnDI9_toggled(bool checked);

    void on_btnDI8_toggled(bool checked);

    void on_btnDI23_toggled(bool checked);

    void on_btnDI22_toggled(bool checked);

    void on_btnDI21_toggled(bool checked);

    void on_btnDI20_toggled(bool checked);

    void on_btnDI19_toggled(bool checked);

    void on_btnDI18_toggled(bool checked);

    void on_btnDI17_toggled(bool checked);

    void on_btnDI16_toggled(bool checked);

    void on_btnDI31_toggled(bool checked);

    void on_btnDI30_toggled(bool checked);

    void on_btnDI29_toggled(bool checked);

    void on_btnDI28_toggled(bool checked);

    void on_btnDI27_toggled(bool checked);

    void on_btnDI26_toggled(bool checked);

    void on_btnDI25_toggled(bool checked);

    void on_btnDI24_toggled(bool checked);

    void on_btnDI39_toggled(bool checked);

    void on_btnDI38_toggled(bool checked);

    void on_btnDI37_toggled(bool checked);

    void on_btnDI36_toggled(bool checked);

    void on_btnDI35_toggled(bool checked);

    void on_btnDI34_toggled(bool checked);

    void on_btnDI33_toggled(bool checked);

    void on_btnDI32_toggled(bool checked);

    void on_btnDI47_toggled(bool checked);

    void on_btnDI46_toggled(bool checked);

    void on_btnDI45_toggled(bool checked);

    void on_btnDI44_toggled(bool checked);

    void on_btnDI43_toggled(bool checked);

    void on_btnDI42_toggled(bool checked);

    void on_btnDI41_toggled(bool checked);

    void on_btnDI40_toggled(bool checked);

    void on_btnDI55_toggled(bool checked);

    void on_btnDI54_toggled(bool checked);

    void on_btnDI53_toggled(bool checked);

    void on_btnDI52_toggled(bool checked);

    void on_btnDI51_toggled(bool checked);

    void on_btnDI50_toggled(bool checked);

    void on_btnDI49_toggled(bool checked);

    void on_btnDI48_toggled(bool checked);

    void on_btnDI63_toggled(bool checked);

    void on_btnDI62_toggled(bool checked);

    void on_btnDI61_toggled(bool checked);

    void on_btnDI60_toggled(bool checked);

    void on_btnDI59_toggled(bool checked);

    void on_btnDI58_toggled(bool checked);

    void on_btnDI57_toggled(bool checked);

    void on_btnDI56_toggled(bool checked);

    void on_btnDI71_toggled(bool checked);

    void on_btnDI70_toggled(bool checked);

    void on_btnDI69_toggled(bool checked);

    void on_btnDI68_toggled(bool checked);

    void on_btnDI67_toggled(bool checked);

    void on_btnDI66_toggled(bool checked);

    void on_btnDI65_toggled(bool checked);

    void on_btnDI64_toggled(bool checked);

    void on_btnDI79_toggled(bool checked);

    void on_btnDI78_toggled(bool checked);

    void on_btnDI77_toggled(bool checked);

    void on_btnDI76_toggled(bool checked);

    void on_btnDI75_toggled(bool checked);

    void on_btnDI74_toggled(bool checked);

    void on_btnDI73_toggled(bool checked);

    void on_btnDI72_toggled(bool checked);

    void on_chbDIgr1_stateChanged(int arg1);

    void on_chbDIgr2_stateChanged(int arg1);

    void on_chbDIgr3_stateChanged(int arg1);

    void on_chbDIgr4_stateChanged(int arg1);

    void on_chbDIgr5_stateChanged(int arg1);

    void on_chbDIgr6_stateChanged(int arg1);

    void on_chbDIgr7_stateChanged(int arg1);

    void on_chbDIgr8_stateChanged(int arg1);

    void on_chbDIgr9_stateChanged(int arg1);

    void on_chbDIgr10_stateChanged(int arg1);

    void on_btnDataDel_clicked();

    void on_btnOpenPts_clicked();

    void on_btnSaveIP_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *updatetimer;
    QTimer *svlifetime;

protected:
    void closeEvent(QCloseEvent *e);

};
#endif // MAINWINDOW_H

