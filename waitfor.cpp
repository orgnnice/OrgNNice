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
    ui->addnew_waitfor->setStyleSheet("#addnew_waitfor{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew_waitfor:hover{color: #000; border: 2px solid #446CB3;}");
    ui->addnew_waitfor->setMinimumSize(QSize(30, 30));
    ui->addnew_waitfor->setMaximumSize(QSize(30, 30));

    this->waitItems = current;
    for(int i=0;i<waitItems.length();i++)
    {

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);

        QFont font1;
        font1.setPointSize(11);

        QLabel *label_desc = new QLabel(waitItems[i].getDescription());
        label_desc->setMinimumSize(QSize(435, 25));
        label_desc->setMaximumSize(QSize(16777215, 25));
        label_desc->setFont(font1);

        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);
        int a = waitItems[i].getSubjectID();
        //QString z = pDBh->select("name", "SchoolSubject", "pk_id='" + a + "'").replace('"',"");
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(145, 25));
        label_subj->setMaximumSize(QSize(145, 25));
        label_subj->setFont(font1);

        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(60, 25));
        checkBox->setMaximumSize(QSize(60, 25));
        checkBox->setStyleSheet(QStringLiteral("padding-left: 25px;"));

        horizontalLayout->addWidget(checkBox, 0, Qt::AlignVCenter);

        ui->verticalLayout_2->addLayout(horizontalLayout);
    }
}
