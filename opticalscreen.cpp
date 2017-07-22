#include "opticalscreen.h"
#include <QHBoxLayout>

OpticalScreen::OpticalScreen(QWidget *parent) : QWidget(parent)
{
    screenLabel = new QLabel(tr("光屏处摄像机"));
    screenLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    screenLabel->setStyleSheet ("background-color: rgb(0,0,255);");
    screenLabel->setAlignment(Qt::AlignCenter);
    openCamBtn = new QPushButton(tr("打开摄像机"));
    openCamBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    workPatternLabel = new QLabel(tr("工作模式"));
    patternComboBox = new QComboBox();
    patternComboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    patternComboBox->insertItem(0,tr("选区衍射(SAD)"));
    patternComboBox->insertItem(1,tr("高分辨像(HRF)"));
    patternComboBox->insertItem(2,tr("明场像(BF)"));
    patternComboBox->insertItem(3,tr("暗场像(DF)"));
    confirmBtn = new QPushButton(tr("确定"));
    confirmBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QHBoxLayout *botton = new QHBoxLayout();
    botton->setSpacing(8);
    botton->addWidget(openCamBtn);
    botton->addWidget(workPatternLabel);
    botton->addWidget(patternComboBox);
    botton->addWidget(confirmBtn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(8);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(screenLabel);
    mainLayout->addLayout(botton);
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);

}
