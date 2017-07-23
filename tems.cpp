#include "tems.h"

tems::tems(QWidget *parent)
    : QWidget(parent)
{
    //初始化设置相机参数
    aperture1 = new Aperture(1);
    aperture1->Init(idCamera[0]);
    aperture2 = new Aperture(2);
    aperture2->Init(idCamera[1]);
    opticalscreen = new OpticalScreen();
    opticalscreen->Init(idCamera[2]);
    resultpic = new ResultPic();
    selectandresult = new SelectAndResult();

    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(2);
    mainLayout->setSpacing(4);
    mainLayout->addWidget(opticalscreen,0,0);
    mainLayout->addWidget(resultpic,0,1);
    mainLayout->addWidget(selectandresult,0,3,2,1);
    mainLayout->addWidget(aperture1,1,0);
    mainLayout->addWidget(aperture2,1,1);

    //---------------连接信号和槽--------------//
    //每次得到距离立马给选择个结果界面发送更新距离的消息
    connect(resultpic,SIGNAL(hasGetDistance_Signal()),this,SLOT(on_Widget_resultpic_setDistance()));
    //采取手动测量的信号给输出结果框架
    connect(resultpic,SIGNAL(ManualWayInfo_Singal()),selectandresult,SLOT(MethodInfo()));
    //
    connect(opticalscreen,SIGNAL(hasConfirm_Signal()),this,SLOT(on_Widget_resultpic_setPic()));
}

tems::~tems()
{
    delete aperture1;
    delete aperture2;
    delete opticalscreen;
    delete resultpic;
    delete selectandresult;
}

void tems::on_Widget_resultpic_setDistance()
{
    selectandresult->setDistance(resultpic->getDistance());
}

void tems::on_Widget_resultpic_setPic()
{
    selectandresult->setMeasurePattern(opticalscreen->getMeasurePattern());
    resultpic->setMeasurePattern(opticalscreen->getMeasurePattern());
    resultpic->setPic(opticalscreen->getConfirmedPic());
}
