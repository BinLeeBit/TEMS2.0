#include "resultpic.h"
#include <QHBoxLayout>

ResultPic::ResultPic(QWidget *parent) : QWidget(parent)
{
    screenLabel = new QLabel(tr("处理图片"));
    screenLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    screenLabel->setAlignment(Qt::AlignCenter);
    screenLabel->setStyleSheet ("background-color: rgb(0,0,255);");
    editPicBtn = new QPushButton(tr("编辑"));
    editPicBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    savePicBtn = new QPushButton(tr("保存"));
    savePicBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QHBoxLayout *botton = new QHBoxLayout();
    botton->setMargin(0);
    botton->addWidget(editPicBtn);
    botton->addWidget(savePicBtn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(8);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(screenLabel);
    mainLayout->addLayout(botton);

    //--------------链接信号与槽---------------//
    connect(editPicBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_editPicBtn_clicked()));
}

void ResultPic::on_pushButton_editPicBtn_clicked()
{
    editPicWidget = new EditPic(0);
    editPicWidget->setEnabled(true);
    editPicWidget->resize(screenLabel->width(),screenLabel->height());
    editPicWidget->show();
    connect(editPicWidget,SIGNAL(confirmBtn_Signal()),this,SLOT(on_getDistance()));
}

void ResultPic::on_getDistance()
{
    pointsDistance = editPicWidget->getLineLenth();
    emit hasGetDistance_Signal();
}

float ResultPic::getDistance()
{
    return pointsDistance;
}
