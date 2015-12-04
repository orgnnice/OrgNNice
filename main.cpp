#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>
#include <dbhandler.h>
#include <writtennote.h>
#include <attachement.h>
#include <mtextedit.h>
#include <subject.h>
#include <mainwindow.h>


int main(int argc, char **argv)
{

    QApplication app (argc, argv);
    DBHandler dbh = DBHandler(QDir::homePath() + QDir::separator());

    //set the dbHandler
    //subject::setDBH(dbh);

    //get all subjects from the database with contents
    QList<subject> allsubjects = dbh.queryWithReturnSubjectList("SELECT * FROM schoolsubject");





    MainWindow w;
    w.show();
    return app.exec();

}


