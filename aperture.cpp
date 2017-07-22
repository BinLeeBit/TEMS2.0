#include "aperture.h"
#include <QHBoxLayout>

Aperture::Aperture(QWidget *parent) : QWidget(parent)
{
    screenLabel = new QLabel(tr("光屏处摄像机"));
    screenLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    screenLabel->setAlignment(Qt::AlignCenter);
    screenLabel->setStyleSheet ("background-color: rgb(0,0,255);");
    openCamBtn = new QPushButton(tr("打开摄像机"));
    openCamBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    savePicBtn = new QPushButton(tr("保存"));
    savePicBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QHBoxLayout *botton = new QHBoxLayout();
    botton->setMargin(0);
    botton->addWidget(openCamBtn);
    botton->addWidget(savePicBtn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(8);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(screenLabel);
    mainLayout->addLayout(botton);
    connect(openCamBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_openCamBtn_clicked()));
}

void Aperture::on_pushButton_openCamBtn_clicked()
{

}
