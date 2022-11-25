#ifndef CMDPROGRAM_H
#define CMDPROGRAM_H

#include <QWidget>

namespace Ui {
class CmdProgram;
}

class CmdProgram : public QWidget
{
    Q_OBJECT

public:
    explicit CmdProgram(QWidget *parent = nullptr);
    ~CmdProgram();

private:
    Ui::CmdProgram *ui;
};

#endif // CMDPROGRAM_H
