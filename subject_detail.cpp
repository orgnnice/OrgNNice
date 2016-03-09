#include "subject_detail.h"
#include "ui_subject_detail.h"
#include <QDebug>
#include <QDialog>
#include <QSignalMapper>
#include "main.h"
#include <QList>
#include "subject.h"

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
    ui->label->setText(subdet.getName());
    ui->label_1->setText("Anzahl der Mitschriften: "+QString::number(subdet.getWrittenNotesSize()));
    //QList<Subject> all = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    int a = 2;
    int line = 0;
    int col = 0;
    noteList = subdet.getWrittenNotes();
    QString dateformat = "dd.MM.yyyy";

    for(int i=0;i<subdet.getWrittenNotesSize();i++){
        QPushButton *pButton = new QPushButton(ui->scrollAreaWidgetContents);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QIcon icon;
        icon.addFile(QStringLiteral("mitschirft.png"), QSize(), QIcon::Normal, QIcon::On);
        pButton->setIcon(icon);
        pButton->setObjectName(QStringLiteral("mitschriftButton"));
        pButton->setIconSize(QSize(50, 100));
        pButton->setAutoExclusive(false);
        pButton->setMinimumWidth(70);
        pButton->setMinimumHeight(100);
        pButton->setStyleSheet("#mitschriftButton{background-color: #fff; color: #23121C; border: 1px solid #446CB3;}"
                                      "#mitschriftButton:hover{background-color: #446CB3; border: 1px solid #fff;}");
        qDebug() << noteList[i].getTimestamp();
        QLabel *labelFilename = new QLabel(noteList[i].getTimestamp().toString("dd.MM.yyyy"));
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
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Org'n'Nice");
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->setText(QString("<h1>Du bist die Dümmste Person dieser Welt!</h1>"));
    dialog->show();
}

void subject_detail::on_pushButton_6_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->setText(QString("Du bist die Dümmste Person dieser Welt!"));
    rte->show();
}

void subject_detail::on_pushButton_4_clicked()
{
    //QDialog *dialog = new QDialog();
    //rte = new MRichTextEdit(); // Be sure to destroy you window somewhere
    //rte->show();
}

void subject_detail::on_pushButton_3_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->setText(QString("Du bist die Dümmste Person dieser Welt!"));
    rte->show();
}

void subject_detail::on_pushButton_5_clicked()
{
    /*MRichTextEdit *rte = new MRichTextEdit(this);
    QGridLayout *gl = new QGridLayout(this);
    this->addWidget(rte,0,0,1,1);
    this->setWindowTitle(QObject::tr("Org'N'Nice"));
    this->setMinimumWidth (400);
    this->setMinimumHeight(400);
    this->show();*/
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this);
    rte->setText(QString("Du bist die Dümmste Person dieser Welt!"));
    rte->show();
}

void subject_detail::on_addnew_clicked()
{
    newWrittenNote = new C_WrittenNote();
    newWrittenNote->setSubject(subdet);// Be sure to destroy you window somewhere
    newWrittenNote->show();
}

void subject_detail::on_pushButton_clicked()
{
   QList<QString> with;
   QList<QString> without;
   with << ui->textEdit->toPlainText();
   without << "";
   qDebug() << "Search for: " << ui->textEdit->toPlainText();
   qDebug() << "QList: " << with;
   qDebug() << "WithOut: " << without;
   QList<WrittenNote> result= subdet.getWrittenNotesWithWithout(with, without);
   qDebug() << "Search WrittenNote-ID: " << result[0].getTags();
}
