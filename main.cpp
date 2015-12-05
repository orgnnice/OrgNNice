#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>
#include <dbhandler.h>
#include <writtennote.h>
#include <mtextedit.h>
#include <subject.h>
#include <mainwindow.h>
#include "main.h"

DBHandler* pDBh;

int main(int argc, char **argv)
{

    QApplication app (argc, argv);
    pDBh = new DBHandler(QDir::homePath() + QDir::separator());

    //get all subjects from the database with contents
    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");




    //MainWindow w;
    //w.show();
    return app.exec();
}


