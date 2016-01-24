#ifndef WAITFOR_H
#define WAITFOR_H

#include <QDialog>
#include "waitfor.h"
#include "new_waitfor.h"

namespace Ui {
class WaitFor;
}

class WaitFor : public QDialog
{
    Q_OBJECT

public:
    explicit WaitFor(QWidget *parent = 0);
    ~WaitFor();

private slots:
    void on_addnew_3_clicked();

    void on_addnew_waitfor_clicked();

private:
    Ui::WaitFor *ui;
    New_WaitFor *add_waitFor;
};

#endif // WAITFOR_H
