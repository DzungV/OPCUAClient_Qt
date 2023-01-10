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
    void ReadData(UA_Client *client);

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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *updatetimer;

protected:
    void closeEvent(QCloseEvent *e);

};
#endif // MAINWINDOW_H

