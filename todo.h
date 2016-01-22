#ifndef TODO_H
#define TODO_H

#include <QDialog>
#include <new_todo.h>

namespace Ui {
class toDo;
}

class toDo : public QDialog
{
    Q_OBJECT

public:
    explicit toDo(QWidget *parent = 0);
    ~toDo();

private slots:
    void on_addnew_clicked();

    void on_toDobut_clicked();

private:
    Ui::toDo *ui;
    new_toDo *add_toDo;
};

#endif // TODO_H
