#ifndef SUBJECT_DETAIL_H
#define SUBJECT_DETAIL_H

#include <QMainWindow>
#include <QPushButton>
#include "mrichtextedit.h"
#include "ui_subject_detail.h"

namespace Ui {
class subject_detail;
}

class subject_detail : public QMainWindow
{
    Q_OBJECT

public:
    explicit subject_detail(QWidget *parent = 0);
    ~subject_detail();

public slots:
   void openNote();

private:
    Ui::subject_detail *ui;
    MRichTextEdit *newWindow;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
};

#endif // SUBJECT_DETAIL_H
