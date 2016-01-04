#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
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

private slots:
   /*void openNewWindow();
   void openSubject();*/

private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;
};

#endif // MAINWINDOW_H
