#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QDialog>
#include <writtennote.h>
#include "mrichtextedit.h"


namespace Ui {
class SearchResult;
}

class SearchResult : public QDialog
{
    Q_OBJECT

public:
    explicit SearchResult(QWidget *parent = 0);
    ~SearchResult();
    QList<WrittenNote> res;
    QString curmess;

public slots:
    void setResult(QList<WrittenNote> cur, QString message);
    void textDet(int list);
    void deleteWrittenNote(int item);
    void update();

private:
    Ui::SearchResult *ui;
    MRichTextEdit *rte;
};

#endif // SEARCHRESULT_H
