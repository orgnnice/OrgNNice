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

class MainWindow : public QMainWindow, protected Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void openNewWindow();
   void openSubject();
   void openRTE();

private:
    Ui::MainWindow *ui;
    //QPushButton *addnew;
    QPushButton *detsub;
    QPushButton *writn;
    c_subject *newCre;
    subject_detail *detSubject;
    MRichTextEdit *rte;
};

#endif // MAINWINDOW_H
