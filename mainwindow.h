#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>


#include <mythread.h>
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

    MyThread *mThread;






    void ClientConnect (int status);



public slots:
    void UpdateTimerTick();
    void IOAlarmTick();
    void Clock();
    void ServerTimeout();
    void JogRBTimer();
    void ReadData(UA_Client *client);
    void Alarm(UA_Client *client);
    void ReadDeltaData(UA_Client *client);
    void ReadDI(UA_Client *client);
    void DisplayDI();
    void JogProcess(int number);
    void SetSttbar(bool bset);


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


    void on_cbEnableDO_stateChanged(int arg1);

    void on_chbDOgr1_stateChanged(int arg1);

    void on_chbDOgr2_stateChanged(int arg1);

    void on_chbDOgr3_stateChanged(int arg1);

    void on_chbDOgr4_stateChanged(int arg1);

    void on_chbDOgr5_stateChanged(int arg1);

    void on_chbDOgr6_stateChanged(int arg1);

    void on_chbDOgr7_stateChanged(int arg1);

    void on_chbDOgr8_stateChanged(int arg1);

    void on_chbDOgr9_stateChanged(int arg1);

    void on_chbDOgr10_stateChanged(int arg1);



    void on_btnDO1_toggled(bool checked);

    void on_btnDO2_toggled(bool checked);

    void on_btnDO3_toggled(bool checked);

    void on_btnDO4_toggled(bool checked);

    void on_btnDO5_toggled(bool checked);

    void on_btnDO6_toggled(bool checked);

    void on_btnDO7_toggled(bool checked);

    void on_btnDO8_toggled(bool checked);


    void on_combSeclvl_currentTextChanged(const QString &arg1);

    void on_btnOkpass_clicked();

    void on_btnRunprg_clicked();

    void on_btnPauseprg_clicked();

    void on_btnStopprg_clicked();

    void on_btnRBMode_toggled(bool checked);

    void on_btnRBCLock_toggled(bool checked);

    void on_btnRBServo_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *updatetimer;
    QTimer *svlifetime;
    QTimer *IOAlarmtimer;




protected:
    void closeEvent(QCloseEvent *e);

};
#endif // MAINWINDOW_H

