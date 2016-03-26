#include "subject_detail.h"
#include "ui_subject_detail.h"
#include <QDebug>
#include <QDialog>
#include <QSignalMapper>
#include "main.h"
#include <QList>
#include "subject.h"
#include "mainwindow.h"

subject_detail::subject_detail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subject_detail)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

subject_detail::~subject_detail()
{
    delete ui;
}

void subject_detail::setSubDet(Subject cur)
{
    this->subdet = cur;
    qDebug() << "Subjectname: " << subdet.getName();
    qDebug() << "Anzahl der Mitschriften:" << subdet.getWrittenNotesSize();
    ui->label_2->setText(subdet.getName());
    ui->label_3->setText(QString::number(subdet.getWrittenNotesSize()) + " Mitschriften");

    ui->addnew_2->setStyleSheet("#addnew_2{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew_2:hover{color: #000; border: 1px solid #446CB3;}");

    ui->pushButton_2->setStyleSheet("#pushButton_2{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#pushButton_2:hover{color: #000; border: 1px solid #446CB3;}");

    //QList<Subject> all = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    int a = 2;
    int line = 0;
    int col = 0;
    noteList = subdet.getWrittenNotes();

    for(int i=0;i<subdet.getWrittenNotesSize();i++){
        QPushButton *pButton = new QPushButton(ui->scrollAreaWidgetContents);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QPixmap pixmap = QPixmap (":/images/icons/icon_writtennote_with_text.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setObjectName(QStringLiteral("mitschriftButton"));
        pButton->setIconSize(QSize(70, 100));
        pButton->setAutoExclusive(false);
        pButton->setMinimumWidth(80);
        pButton->setMinimumHeight(110);
        pButton->setStyleSheet("#mitschriftButton{background-color: #fff; color: #23121C; border: 1px solid #446CB3; border-radius: 2px;}"
                                      "#mitschriftButton:hover{background-color: #446CB3; border: 1px solid #fff;}");
        qDebug() << noteList[i].getTimestamp();
        QLabel *labelFilename = new QLabel(noteList[i].getTimestamp().toString("dd.MM.yyyy"));
        labelFilename->setStyleSheet(QStringLiteral("padding-bottom: 25px; font-family: 'Yu Gothic UI';"));
        QSpacerItem *vSpacer;
        vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(pButton, 0, Qt::AlignHCenter);
        verticalLayout->addWidget(labelFilename, 0, Qt::AlignHCenter);
        verticalLayout->addItem(vSpacer);
        if(i > a){
            a += 3;
            line++;
            col = 0;
        }
        //ui->gridLayout->addLayout(verticalLayout,line,col,1,1);
        ui->gridLayout->addLayout(verticalLayout,line,col,1,1);
        col++;
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(textDet(int)));
    }
}

void subject_detail::textDet(int index){
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Org'n'Nice");
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->setText(noteList[index].getContent().replace("^", "'"));
    rte->setNote(noteList[index]);
    dialog->show();
}

void subject_detail::on_pushButton_2_clicked()
{
    opensearch = new SearchDialog();
    opensearch->selsub = subdet;
    opensearch->show();
}

void subject_detail::on_addnew_2_clicked()
{
    newWrittenNote = new C_WrittenNote(this);
    newWrittenNote->setSubject(subdet);// Be sure to destroy you window somewhere
    newWrittenNote->show();
}

void subject_detail::update()
{
qDebug() << "Started Update";
qDebug() << "Name des ersten Subject";
subdet.updateSubject();
this->setSubDet(subdet);
MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
// check parent is not null
parent->update();
}
