#include "SelectAndResult.h"
#include <QGridLayout>
#include <QDateTime>
#include <cstdlib>
//#include <QProcess>
#include <QApplication>

SelectAndResult::SelectAndResult(QWidget *parent) : QWidget(parent)
{
    //-------------界面设置------------------//
    motorCtrlLabel = new QLabel(tr("电机控制"));
    motorCtrlBtn = new QPushButton(tr("电脑控制"));
    motorCtrlBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    measureMethodLabel = new QLabel(tr("测量方式"));
    measureMethodBtn = new QPushButton(tr("自动测量"));
    measureMethodBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    dateLabel =new QLabel(tr("当前时间"));
    displayDateLabel = new QLabel();
    QGridLayout *rightTopLayout = new QGridLayout();
    rightTopLayout->setSpacing(8);
    rightTopLayout->addWidget(motorCtrlLabel,0,0);
    rightTopLayout->addWidget(motorCtrlBtn,0,1);
    rightTopLayout->addWidget(measureMethodLabel,1,0);
    rightTopLayout->addWidget(measureMethodBtn,1,1);
    rightTopLayout->addWidget(dateLabel,2,0);
    rightTopLayout->addWidget(displayDateLabel,2,1);

    distanceLabel = new QLabel(tr("测量结果"));
    distanceTextBrowser = new QTextBrowser();
    distanceTextBrowser->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    QVBoxLayout *rightBottonLayout = new QVBoxLayout();
    rightBottonLayout->setSpacing(15);
    rightBottonLayout->addWidget(distanceLabel);
    rightBottonLayout->addWidget(distanceTextBrowser);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(12);
    mainLayout->setSpacing(30);
    mainLayout->addLayout(rightTopLayout);
    mainLayout->addLayout(rightBottonLayout);

    //--------------功能部分--------------------//
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);                     //1s更新一次
    connect(motorCtrlBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_motorCtrlBtn_clicked()));
}

void SelectAndResult::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("MM-dd hh:mm:ss dddd");
    displayDateLabel->setText(str);
}

void SelectAndResult::on_pushButton_motorCtrlBtn_clicked()
{
    QString application = QApplication::applicationDirPath().append(
                "/motor/WindowsFormsApplication1.application");
    system(application.toLatin1().data());
    //QProcess *process = new QProcess(this);
    //process->start(application);
}

