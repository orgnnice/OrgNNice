#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <subject.h>
#include <searchresult.h>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    Subject selsub;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SearchDialog *ui;
    SearchResult *out;
};

#endif // SEARCHDIALOG_H
