#ifndef C_SUBJECT_H
#define C_SUBJECT_H

#include <QDialog>
#include "ui_c_subject.h"

namespace Ui {
class c_subject;
}

class c_subject : public QDialog
{
    Q_OBJECT

public:
    explicit c_subject(QWidget *parent = 0);
    ~c_subject();

private:
    Ui::c_subject *ui;
};

#endif // C_SUBJECT_H
