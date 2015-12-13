#ifndef SUBJECT_DETAIL_H
#define SUBJECT_DETAIL_H

#include <QWidget>

namespace Ui {
class Subject_detail;
}

class Subject_detail : public QWidget
{
    Q_OBJECT

public:
    explicit Subject_detail(QWidget *parent = 0);
    ~Subject_detail();

private:
    Ui::Subject_detail *ui;
};

#endif // SUBJECT_DETAIL_H
