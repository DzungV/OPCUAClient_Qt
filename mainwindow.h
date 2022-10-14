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

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *updatetimer;
};
#endif // MAINWINDOW_H
