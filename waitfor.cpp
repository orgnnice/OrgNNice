#include "waitfor.h"
#include "ui_waitfor.h"
#include "qcheckbox.h"
#include "dbhandler.h"
#include "main.h"
#include "subject.h"

WaitFor::WaitFor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitFor)
{
    ui->setupUi(this);
}

WaitFor::~WaitFor()
{
    delete ui;
}

void WaitFor::on_addnew_waitfor_clicked()
{
    add_waitFor = new New_WaitFor();
    add_waitFor->show();
}

void WaitFor::setItemList(QList<WaitForList> current)
{
    this->waitItems = current;
    for(int i=0;i<waitItems.length();i++)
    {

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);

        QFont font1;
        font1.setPointSize(11);

        QLabel *label_desc = new QLabel(waitItems[i].getDescription());
        label_desc->setMinimumSize(QSize(450, 25));
        label_desc->setMaximumSize(QSize(16777215, 25));
        label_desc->setFont(font1);

        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);
        int a = waitItems[i].getSubjectID();
        //QString z = pDBh->select("name", "SchoolSubject", "pk_id='" + a + "'").replace('"',"");
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(100, 25));
        label_subj->setMaximumSize(QSize(16777215, 25));
        label_subj->setFont(font1);

        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(100, 25));
        checkBox->setMaximumSize(QSize(100, 25));
        checkBox->setStyleSheet(QStringLiteral("padding-left: 25px;"));

        horizontalLayout->addWidget(checkBox, 0, Qt::AlignTop);

        ui->verticalLayout_4->setSpacing(6);
        ui->verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        ui->verticalLayout_4->setContentsMargins(0, 0, 0, 0);

        ui->verticalLayout_4->addLayout(horizontalLayout);
    }
}
