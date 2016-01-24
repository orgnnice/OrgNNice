#ifndef NEW_WAITFOR_H
#define NEW_WAITFOR_H

#include <QDialog>

namespace Ui {
class New_WaitFor;
}

class New_WaitFor : public QDialog
{
    Q_OBJECT

public:
    explicit New_WaitFor(QWidget *parent = 0);
    ~New_WaitFor();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::New_WaitFor *ui;
};

#endif // NEW_WAITFOR_H
