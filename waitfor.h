#ifndef WAITFOR_H
#define WAITFOR_H

#include <QDialog>
#include "waitfor.h"
#include "new_waitfor.h"
#include "waitforlist.h"

namespace Ui {
class WaitFor;
}

class WaitFor : public QDialog
{
    Q_OBJECT

public:
    explicit WaitFor(QWidget *parent = 0);
    ~WaitFor();
    QList<WaitForList> waitItems;

public slots:
    void setItemList(QList<WaitForList> current);

private slots:
    void on_addnew_3_clicked();

    void on_addnew_waitfor_clicked();

private:
    Ui::WaitFor *ui;
    New_WaitFor *add_waitFor;
};

#endif // WAITFOR_H
