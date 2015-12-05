#ifndef WRITTENNOTE_H
#define WRITTENNOTE_H

#include <QString>
#include <QDateTime>

class Subject;
class DBHandler;

class WrittenNote
{



private:
//    static DBHandler dbh;
    int id;
    QString text;
    QList<QString> attachements;
    QList<QString> tags;
    QDateTime timestamp;

public:
    WrittenNote();
    WrittenNote(int ID, QString text, QList<QString> attachements,QList<QString> tags,  QDateTime timestamp);
    static void setDBH(DBHandler db_handler);
    void setDate(QDateTime);
    void saveWrittenNote(Subject);
    void addAttachement(QString);
    void addTag(QString newTag);
    int getId();
    QString getContent();
    QDateTime getTimestamp();
    QList<QString> getTags();
    QList<QString> getAttachement();

};

#endif // WRITTENNOTE_H
