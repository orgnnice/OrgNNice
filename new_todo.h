#ifndef NEW_TODO_H
#define NEW_TODO_H

#include <QDialog>

namespace Ui {
class new_toDo;
}

class new_toDo : public QDialog
{
    Q_OBJECT

public:
    explicit new_toDo(QWidget *parent = 0);
    ~new_toDo();
public slots:
    void setSubName(QString subname);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::new_toDo *ui;
};

#endif // NEW_TODO_H
