#include "tems.h"

tems::tems(QWidget *parent)
    : QWidget(parent)
{
    aperture1 = new Aperture();
    aperture2 = new Aperture();
    opticalscreen = new OpticalScreen();
    resultpic = new ResultPic();
    selectandresult = new SelectAndResult();
    /*leftLayout = new QVBoxLayout();
    midLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();
    */
    mainLayout = new QGridLayout(this);

    /*leftLayout->setSpacing(8);
    leftLayout->addWidget(opticalscreen);
    leftLayout->addWidget(aperture1);

    midLayout->setSpacing(8);
    midLayout->addWidget(resultpic);
    midLayout->addWidget(aperture2);
    */

    mainLayout->setMargin(2);
    mainLayout->setSpacing(4);
    mainLayout->addWidget(opticalscreen,0,0);
    mainLayout->addWidget(resultpic,0,1);
    mainLayout->addWidget(selectandresult,0,3,2,1);
    mainLayout->addWidget(aperture1,1,0);
    mainLayout->addWidget(aperture2,1,1);

    //---------------连接信号和槽--------------//
    //每次得到距离立马给选择个结果界面发送更新距离的消息
    connect(resultpic,SIGNAL(hasGetDistance_Signal()),this,SLOT(on_Widget_resultpic_getDistance()));
}

tems::~tems()
{

}

void tems::on_Widget_resultpic_getDistance()
{
    selectandresult->setDistance(resultpic->getDistance());
}
