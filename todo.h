#ifndef TODO_H
#define TODO_H

#include <QDialog>

namespace Ui {
class toDo;
}

class toDo : public QDialog
{
    Q_OBJECT

public:
    explicit toDo(QWidget *parent = 0);
    ~toDo();

private:
    Ui::toDo *ui;
};

#endif // TODO_H
