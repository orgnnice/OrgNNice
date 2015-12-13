#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QPushButton>
#include "c_subject.h"
#include "subject.h"
#include "subject_detail.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void openNewWindow();
   void openSubject();

private:
    Ui::MainWindow *ui;
    QToolButton *addnewsub;
    c_subject *newWindow;
    //subject_detail *selSub;
    /*QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;*/
};

#endif // MAINWINDOW_H
