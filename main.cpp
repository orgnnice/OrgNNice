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

    //WaitForList waitfor = WaitForList("mathe", "Warten auf Mitra", false);
    //WaitForList waitfor2 = WaitForList("deutsch", "Warten auf bessere Zeiten", false);
    QList <WaitForList> wfs =  pDBh->queryWithReturnWaitForListList("SELECT * FROM waitfor");
    qDebug() << "-__--____---__-__-----------_--_--__======>>>>>>>> W a i t f o r - t e s t <<<<<<<<<<<<";
    for(WaitForList wf : wfs)
    {
        qDebug() << "waitfor:" << wf.toString();
    }

//    ToDoItem(QString subject_name, QString description, QDateTime deadline, bool done);
    //ToDoItem("mathe", "HÜ: 419a, 420b, 422f", QDateTime(), false);
    //ToDoItem("deutsch", "faust lesen bis 143", QDateTime(), true);
    //ToDoItem("deutsch", "buchbesprechung schreiben", QDateTime(), false);




    wfs =  pDBh->queryWithReturnWaitForListList("SELECT * FROM waitfor");
    QList <ToDoItem> todos =  pDBh->queryWithReturnToDoItemList("SELECT * FROM todo");

    /*
    qDebug() << "-__--____---__-__-----------_--_--__======>>>>>>>> 2. 0: !!!!!!W a i t f o r - t e s t <<<<<<<<<<<<";
    for(WaitForList wf : wfs)
    {
        qDebug() << "waitfor:" << wf.toString();
    }

    qDebug() << "!!!   !!!!  !!    !!!!!   !!!!! >>>>>>>> TODO  - t e s t <<<<<<<<<<<<";
    for(ToDoItem todo : todos)
    {
        qDebug() << "waitfor:" << todo.toString();
    }


*/
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
    /*


    qDebug() << "!!!   !!!!  !!    !!!!!   !!!!! >>>>>>>> EXPORT  - t e s t <<<<<<<<<<<<";

    ExportImport test = ExportImport(QDir::homePath());
    test.exportDatabase(true,false,false,false,"mathe");
*/
    qDebug() << "!!!   !!!!  !!    !!!!!   !!!!! >>>>>>>> EXPORT  - t e s t ENDE<<<<<<<<<<<<";
    pDBh->DBHandlerStateDebugOut();

    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    MainWindow w;
    w.todoItems = todos;
    w.waitItems = wfs;
    w.setSubList(allsubjects);
    w.show();

    return app.exec();
}
