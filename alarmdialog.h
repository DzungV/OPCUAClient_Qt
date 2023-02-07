#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>

namespace Ui {
class AlarmDialog;
}

class AlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDialog(QWidget *parent = nullptr);
    ~AlarmDialog();

private:
    Ui::AlarmDialog *ui;
};

#endif // ALARMDIALOG_H
