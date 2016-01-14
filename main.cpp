#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>
#include <dbhandler.h>
#include <writtennote.h>
#include <mtextedit.h>
#include <subject.h>
#include <todoitem.h>
#include <mainwindow.h>
#include "main.h"
#include <QDebug>
#include <QDateTime>
#include <waitforlist.h>
#include <exportimport.h>

DBHandler* pDBh;

int main(int argc, char **argv)
{

    QApplication app (argc, argv);
    pDBh = new DBHandler(QDir::homePath(), "orgnnice.db3");


    //get all subjects from the database with contents
    //QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    //Subject(int id, QList <WrittenNote> notes, QString name);



    Subject mathe = Subject("mathe");

    WrittenNote note = WrittenNote("Gute Mitschrift", QDateTime(), "mathe");
    WrittenNote note2 = WrittenNote("Böse Mitschrift", QDateTime(), "mathe");
    mathe.setSubjectName("Chemie");
    mathe.setSubjectName("Chemie");
    mathe.setSubjectName("mathe");
    mathe.setSubjectName("Chemie");
    mathe.setSubjectName("Deutsch");
    mathe.setSubjectName("Englisch");


    note.addTag("fun");
    note.addTag("fun");
    note2.addTag("fun");
    note.removeTag("nonexistingTag");

    ExportImport test = ExportImport(QDir::homePath());
    test.exportDatabase(false,true,false,false,"mathe");

    note2.addTag("nofun");

    note.addAttachement("/home/luki/neu.py");
    note2.addAttachement("/home/luki/neu.py");
    note2.addAttachement("/home/luki/neu2.py");

    //note.addAttachement("/home/luki/mitschrift.txt");

    QList<QString> taglistwith = QList<QString>();
    QList<QString> taglistwithout = QList<QString>();





    taglistwith.append("nofun");
    taglistwith.append("spaß");


    //QList<WrittenNote> notelist  = allsubjects[0].getWrittenNotesWithWithout(taglistwith, taglistwithout);

    //QList<WrittenNote> notelist = allsubjects[0].getWrittenNotes(taglistwith);

    /*
    QList<WrittenNote> funNotes = allsubjects[0].getWrittenNotes(taglistwith);
    qDebug() << "length of funnotes: " << QString::number(funNotes.length());
    qDebug() << "All Notes with tags: 'fun' but without tags 'nofun' ";
    for (WrittenNote n : funNotes)
    {
        qDebug() << "note:" << n.toString();
    }


    qDebug() << "iterate through everything:";
    for (Subject s : allsubjects)
    {
        qDebug() << "Subject: " << s.toString();
        for (WrittenNote n : s.getWrittenNotes())
        {
            qDebug() << "note:" << n.toString();
        }
    }

*/

    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    MainWindow w;
    w.setSubList(allsubjects);
    w.show();
    return app.exec();
}
