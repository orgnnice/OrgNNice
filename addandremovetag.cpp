#include "addandremovetag.h"
#include "ui_addandremovetag.h"
#include "qdebug.h"
#include "QSignalMapper"

AddAndRemoveTag::AddAndRemoveTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAndRemoveTag)
{
    ui->setupUi(this);
}

AddAndRemoveTag::~AddAndRemoveTag()
{
    delete ui;
}

void AddAndRemoveTag::setWrittenNote(WrittenNote cur) {
    selwr = cur;
    QList<QString> tags = selwr.getTags();
    for(int i=0;i<tags.length();i++)
    {
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QHBoxLayout *itemLayout = new QHBoxLayout();
        QFont font1;
        font1.setPointSize(9);

        QLabel *label_Tagname = new QLabel(tags[i]);
        label_Tagname->setFont(font1);
        itemLayout->addWidget(label_Tagname);

        QSpacerItem *hSpacer;
        hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        itemLayout->addSpacerItem(hSpacer);

        QPushButton *pButton = new QPushButton("Löschen");
        itemLayout->addWidget(pButton);

        ui->verticalLayout_2->addLayout(itemLayout);
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, tags[i]);
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(deleteTag(QString)));
    }
    QSpacerItem *vSpacer;
    vSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout_2->addSpacerItem(vSpacer);
}



void AddAndRemoveTag::on_pushButton_clicked()
{
    selwr.addTag(ui->lineEdit->text());
    this->close();
}

void AddAndRemoveTag::deleteTag(QString seltag) {
    qDebug() << "Delete Tag: " << seltag;
    selwr.removeTag(seltag);
    this->close();
}
