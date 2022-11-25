#include "cmdprogram.h"
#include "ui_cmdprogram.h"

CmdProgram::CmdProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmdProgram)
{
    ui->setupUi(this);
}

CmdProgram::~CmdProgram()
{
    delete ui;
}
