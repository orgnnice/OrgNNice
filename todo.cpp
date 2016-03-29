#include "todo.h"
#include "ui_todo.h"
#include "qdebug.h"
#include "dbhandler.h"
#include "main.h"
#include "qcheckbox.h"
#include "mainwindow.h"
#include <QShortcut>

toDo::toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toDo)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");

    QShortcut *shortcut = new QShortcut(QKeySequence(tr("Ctrl+n")),
                             this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_addnew_clicked()));
}

toDo::~toDo()
{
    delete ui;
}

void toDo::on_addnew_clicked()
{
    add_toDo = new new_toDo(this);
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

        QSignalMapper* checkedMapper = new QSignalMapper(this);
        QSignalMapper* deleteMapper = new QSignalMapper(this);

        QWidget *fixedWidget = new QWidget;
        QHBoxLayout *horizontalLayout = new QHBoxLayout(fixedWidget);
        horizontalLayout->setSpacing(7);
        fixedWidget->setFixedHeight(35);

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
        label_desc->setMinimumSize(QSize(270, 25));
        label_desc->setMaximumSize(QSize(16777215, 25));
        label_desc->setFont(font1);
        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);

        int a = toItems[i].getSubjectID();
        qDebug() << "Name of Subject: " << pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a));
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(150, 25));
        label_subj->setMaximumSize(QSize(150, 25));
        label_subj->setFont(font1);
        label_subj->setObjectName(QStringLiteral("labelSub"));
        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(25, 25));
        checkBox->setMaximumSize(QSize(25, 25));
        qDebug() << "Done: " << toItems[i].getDone();
        checkBox->setChecked(toItems[i].getDone());
        horizontalLayout->addWidget(checkBox, 0, Qt::AlignTop);

        QPushButton *pButton = new QPushButton();
        QPixmap pixmap = QPixmap (":/images/icons/icon_waste_white.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setIconSize(QSize(20, 20));
        pButton->setObjectName(QStringLiteral("deleteButton"));
        pButton->setMinimumSize(QSize(25, 25));
        pButton->setMaximumSize(QSize(25, 25));
        pButton->setStyleSheet("#deleteButton{background-color: #F22613; color: #23121C; border: 1px solid #000; border-radius: 2px;}"
                               "#deleteButton:hover{color: #000; border: 1px solid #888;}");
        horizontalLayout->addWidget(pButton, 0, Qt::AlignTop);

        ui->verticalLayout_2->addWidget(fixedWidget, 0, Qt::AlignTop);

        QFrame *line_2 = new QFrame();
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        ui->verticalLayout_2->addWidget(line_2, Qt::AlignTop);

        connect(checkBox, SIGNAL(clicked()), checkedMapper, SLOT(map()));
        checkedMapper->setMapping(checkBox, i);
        connect(checkedMapper, SIGNAL(mapped(int)), this, SLOT(check(int)));

        connect(pButton, SIGNAL(clicked()), deleteMapper, SLOT(map()));
        deleteMapper->setMapping(pButton, i);
        connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(deleteToDo(int)));
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
    this->update();
}

void toDo::deleteToDo(int item){
    toItems[item].deleteToDoItem();
    this->update();
}

void clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void toDo::update()
{
qDebug() << "Started Update";
qDebug() << "Name des ersten Subject";
QList <ToDoItem> alltodos =  pDBh->queryWithReturnToDoItemList("SELECT * FROM todo");
clearLayout(ui->verticalLayout_2);
this->setItemList(alltodos);
MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
// check parent is not null
parent->updateLists();
}

void toDo::new_ToDo(QString subname)
{
    add_toDo = new new_toDo(this);
    add_toDo->show();
    add_toDo->setSubName(subname);
}

