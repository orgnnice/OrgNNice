#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>
#include <dbhandler.h>


int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 DBHandler dbh = DBHandler(QDir::homePath() + QDir::separator());



 return app.exec();

}


