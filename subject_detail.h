#ifndef SUBJECT_DETAIL_H
#define SUBJECT_DETAIL_H

#include <QMainWindow>

namespace Ui {
class subject_detail;
}

class subject_detail : public QMainWindow
{
    Q_OBJECT

public:
    explicit subject_detail(QWidget *parent = 0);
    ~subject_detail();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::subject_detail *ui;
};

#endif // SUBJECT_DETAIL_H
