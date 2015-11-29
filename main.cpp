#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>
#include <dbhandler.h>
#include "mainwindow.h"


int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 DBHandler dbh = DBHandler(QDir::homePath() + QDir::separator());


 MainWindow w;
 w.show();
 return app.exec();

}


