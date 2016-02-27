#ifndef C_SUBJECT_H
#define C_SUBJECT_H

#include <QDialog>
#include "ui_c_subject.h"
#include "subject.h"

namespace Ui {
class c_subject;
}

class c_subject : public QDialog, private Ui::c_subject
{
    Q_OBJECT

public:
    explicit c_subject(QWidget *parent = 0);
    ~c_subject();
    //MainWindow parmain;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_buttonBox_rejected();

private:
    Ui::c_subject *ui;
};

#endif // C_SUBJECT_H
