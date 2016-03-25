#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include "exportimport.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = 0);
    ~ExportDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

private:
    Ui::ExportDialog *ui;
    ExportImport *eport;
};

#endif // EXPORTDIALOG_H
