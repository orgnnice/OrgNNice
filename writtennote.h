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
    int subject_ID;

public:
    WrittenNote();
    WrittenNote(int ID, QString text, QList<QString> attachements,QList<QString> tags,  QDateTime timestamp, int subject_ID);

    WrittenNote(QString content, QDateTime ts, QString subject_name);
    WrittenNote(QString content, QDateTime ts, int subject_ID);

    static void setDBH(DBHandler db_handler);
    void setDate(QDateTime);
    void saveWrittenNote(Subject);
    void addAttachement(QString);
    void addTag(QString newTag);
    void removeTag(QString tag);
    void removeAttachement(QString);
    int getId();
    QString getContent();
    QDateTime getTimestamp();
    QList<QString> getTags();
    QList<QString> getAttachement();

    QString toString();

    int getSubject_ID() const;
    void setSubject_ID(int value);
};

#endif // WRITTENNOTE_H
