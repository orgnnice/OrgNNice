#include "todo.h"
#include "ui_todo.h"
#include "qdebug.h"
#include "dbhandler.h"
#include "main.h"
#include "qcheckbox.h"

toDo::toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toDo)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

toDo::~toDo()
{
    delete ui;
}

void toDo::on_addnew_clicked()
{
    add_toDo = new new_toDo();
    add_toDo->show();
}

void toDo::setItemList(QList<ToDoItem> current)
{
    ui->addnew->setStyleSheet("#addnew{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew:hover{color: #000; border: 1px solid #446CB3;}");
    ui->addnew->setMinimumSize(QSize(30, 30));
    ui->addnew->setMaximumSize(QSize(30, 30));

    this->toItems = current;
    qDebug() << toItems.length();
    for(int i=0;i<toItems.length();i++)
    {
        qDebug() << "Aufgabe: " << toItems[i].getDescription();

        QSignalMapper* signalMapper = new QSignalMapper(this);

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);

        QFont font1;
        font1.setPointSize(9);

        QLabel *label_date = new QLabel(toItems[i].getDeadline().toString("dd.MM.yyyy hh:mm"));
        qDebug() << "QDateTime: "<< toItems[i].getDeadline().date();
        qDebug() << "Date: " << toItems[i].getDeadline().toString(Qt::TextDate);
        label_date->setMinimumSize(QSize(120, 25));
        label_date->setMaximumSize(QSize(120 , 25));
        label_date->setFont(font1);

        horizontalLayout->addWidget(label_date, 0, Qt::AlignTop);

        QLabel *label_desc = new QLabel(toItems[i].getDescription());
        label_desc->setMinimumSize(QSize(320, 25));
        label_desc->setMaximumSize(QSize(16777215, 16777215));
        label_desc->setFont(font1);
        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);

        int a = toItems[i].getSubjectID();
        qDebug() << "Name of Subject: " << pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a));
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(140, 25));
        label_subj->setMaximumSize(QSize(140, 25));
        label_subj->setFont(font1);
        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(30, 25));
        checkBox->setMaximumSize(QSize(30, 25));
        qDebug() << "Done: " << toItems[i].getDone();
        checkBox->setChecked(toItems[i].getDone());
        horizontalLayout->addWidget(checkBox, 0, Qt::AlignTop);

        QPushButton *pButton = new QPushButton();
        QPixmap pixmap = QPixmap (":/images/icons/icon_waste.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setMinimumSize(QSize(25, 25));
        pButton->setMaximumSize(QSize(25, 25));
        horizontalLayout->addWidget(pButton, 0, Qt::AlignTop);

        ui->verticalLayout_2->addLayout(horizontalLayout);

        QFrame *line_2 = new QFrame();
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        ui->verticalLayout_2->addWidget(line_2, Qt::AlignTop);

        connect(checkBox, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(checkBox, i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(check(int)));
    }
}

void toDo::check(int item){
    if(toItems[item].getDone()) {
        toItems[item].setDone(false);
        qDebug() << toItems[item].getDone();
    }else{
        toItems[item].setDone(true);
        qDebug() << toItems[item].getDone();
    }
    toItems[item].updateToDoItem();
}
