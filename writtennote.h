#ifndef WRITTENNOTE_H
#define WRITTENNOTE_H

#include <QString>
#include <QDateTime>
#include <attachement.h>


class WrittenNote
{
private:
    int id;
    QString text;
    QList<Attachement> attachements;
    QList<QString> tags;
    QDateTime timestamp;

public:
    void setDate(QDateTime);
    void saveWrittenNote(QString);
    void addAttachement(Attachement);
    void addTag(QString newTag);
    QDateTime getTimestamp() const;
    QList<QString> getTags() const;
    WrittenNote();
    WrittenNote(QString text, QList<QString> tags, QList<Attachement> attachements, QDateTime timestamp);
};

#endif // WRITTENNOTE_H
