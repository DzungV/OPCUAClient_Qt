#ifndef CODE_EDITOR_H
#define CODE_EDITOR_H


#include <QMainWindow>
#include <highlighter.h>
#include <QShortcut>
#include "QSettings"
#include <QPlainTextEdit>

#include "files.h"
#include "search.h"
#include "utils/conversion.h"
#include "utils/templates.h"

namespace Ui {
class Code_Editor;
}

class Code_Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Code_Editor(QWidget *parent = nullptr);
    ~Code_Editor();
    void openWith(QString);

private:
    Ui::Code_Editor *ui;
};

#endif // CODE_EDITOR_H
