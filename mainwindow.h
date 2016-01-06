#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPointer>
#include "ui_mainwindow.h"
#include "c_subject.h"
#include "subject_detail.h"
#include "mrichtextedit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void openNewWindow();
   void openSubject();
   void openRTE();

   void on_pushButton_10_clicked();

   void on_addnew_clicked();

   void on_pushButton_9_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_3_clicked();

   void on_pushButton_8_clicked();

   void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *detsub;
    QPushButton *writn;
    c_subject *newCre;
    subject_detail *detSubject;
    MRichTextEdit *rte;
};

#endif // MAINWINDOW_H
