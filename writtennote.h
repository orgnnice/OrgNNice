#ifndef WRITTENNOTE_H
#define WRITTENNOTE_H

#include <QString>
#include <QDateTime>
#include <attachement.h>


class DBHandler;

class WrittenNote
{



private:
    static DBHandler dbh;
    int id;
    QString text;
    QList<Attachement> attachements;
    QList<QString> tags;
    QDateTime timestamp;

public:
    WrittenNote();
    WrittenNote(QString text, QList<QString> tags, QList<Attachement> attachements, QDateTime timestamp);
    static void setDBH(DBHandler db_handler);
    void setDate(QDateTime);
    void saveWrittenNote(QString);
    void addAttachement(Attachement);
    void addTag(QString newTag);
    QString getContent() const;
    QDateTime getTimestamp() const;
    QList<QString> getTags() const;
    QList<Attachement> getAttachement() const;

};

#endif // WRITTENNOTE_H
