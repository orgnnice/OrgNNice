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
    ui->pushButton->setObjectName(QStringLiteral("addNewTag"));
    ui->pushButton->setStyleSheet("#addNewTag{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                                          "#addNewTag:hover{color: #000; border: 1px solid #446CB3;}");
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

        QPushButton *pButton = new QPushButton();
        pButton->setObjectName(QStringLiteral("deleteTagButton"));
        QPixmap pixmap = QPixmap (":/images/icons/icon_waste_white.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setIconSize(QSize(20, 20));
        pButton->setMinimumSize(QSize(25, 25));
        pButton->setMaximumSize(QSize(25, 25));
        pButton->setStyleSheet("#deleteTagButton{background-color: #F22613; color: #23121C; border: 1px solid #000; border-radius: 2px;}"
                               "#deleteTagButton:hover{color: #000; border: 1px solid #888;}");
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
