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
#include <QDebug>
#include <QDateTime>

DBHandler* pDBh;

int main(int argc, char **argv)
{

    QApplication app (argc, argv);
    pDBh = new DBHandler(QDir::homePath());

    //get all subjects from the database with contents
    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    //    Subject(int id, QList <WrittenNote> notes, QString name);


    //Subject mathe = Subject("mathe");
    //allsubjects.append(mathe);
    qDebug() << "allsubjects: " << allsubjects[0].toString();
    qDebug() << "allsubjects: ";

    QDateTime ts = QDateTime::currentDateTime();


    WrittenNote noteWithTags = WrittenNote();

    WrittenNote note = allsubjects[0].getWrittenNotes()[0];

    note.removeTag("fun");


    for (Subject s : allsubjects)
    {
        qDebug() << "Subject: " << s.toString();
        for (WrittenNote n : s.getWrittenNotes())
        {
            qDebug() << n.toString();
        }
    }


    //MainWindow w;
    //w.show();
    return app.exec();
}


