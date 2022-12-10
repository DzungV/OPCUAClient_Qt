#include "code_editor.h"
#include "ui_code_editor.h"

Code_Editor::Code_Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Code_Editor)
{
    ui->setupUi(this);
}

Code_Editor::~Code_Editor()
{
    delete ui;
}
