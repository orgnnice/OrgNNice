#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPointer>
#include "ui_mainwindow.h"
#include "c_subject.h"
#include "subject_detail.h"
#include "subject.h"
#include "todo.h"
#include "waitfor.h"
#include "exportdialog.h"
#include "todoitem.h"
#include "waitforlist.h"

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
    QList<ToDoItem> todoItems;
    QList<WaitForList> waitItems;

public slots:
    void setSubList(QList<Subject> list);
    void update();

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

   void on_pushButton_clicked();

   void on_toDo_clicked();

   void on_toDobut_clicked();

   void on_import_2_clicked();

   void on_export_2_clicked();

   void on_waitForbut_clicked();

   void on_addnew_2_clicked();

private:
    Ui::MainWindow *ui;
    c_subject *newCre;
    subject_detail *detSubject;
    toDo *toList;
    WaitFor *waitList;
    ExportDialog *exportDia;

};

#endif // MAINWINDOW_H
