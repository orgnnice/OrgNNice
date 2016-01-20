#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPointer>
#include "ui_mainwindow.h"
#include "c_subject.h"
#include "subject_detail.h"
#include "subject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<Subject> sublist;
    Subject selected;

public slots:
    void setSubList(QList<Subject> list);


private slots:
   void openNewWindow();

   void on_pushButton_10_clicked();

   void on_addnew_clicked();

   void on_pushButton_9_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_8_clicked();

   void on_pushButton_5_clicked();

   void subDetail(int index);



private:
    Ui::MainWindow *ui;
    c_subject *newCre;
    subject_detail *detSubject;

};

#endif // MAINWINDOW_H
