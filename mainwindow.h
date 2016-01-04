#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPointer>
#include "ui_mainwindow.h"
#include "c_subject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void openNewWindow();
   /*void openSubject();*/

private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;
    c_subject *newCre;
};

#endif // MAINWINDOW_H
