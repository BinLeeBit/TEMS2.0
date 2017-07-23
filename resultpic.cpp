#include "resultpic.h"
#include <QHBoxLayout>

ResultPic::ResultPic(QWidget *parent) : QWidget(parent)
{
    screenLabel = new QLabel(tr("处理图片"));
    screenLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    screenLabel->setAlignment(Qt::AlignCenter);
    screenLabel->setStyleSheet ("background-color: rgb(0,0,255);");
    editPicBtn = new QPushButton(tr("编辑"));
    editPicBtn->setEnabled(false);
    editPicBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    savePicBtn = new QPushButton(tr("保存"));
    savePicBtn->setEnabled(false);
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
    emit ManualWayInfo_Singal();
    editPicWidget = new EditPic(0);
    editPicWidget->setEnabled(true);
    editPicWidget->resize(screenLabel->width(),screenLabel->height());
    editPicWidget->show();
    editPicWidget->setSrcPic(resultPic);
    connect(editPicWidget,SIGNAL(confirmBtn_Signal()),this,SLOT(on_getDistance()));
}

void ResultPic::on_getDistance()
{
    pointsDistance = editPicWidget->getLineLenth();
    resultPic  = editPicWidget->getDstPic();
    screenLabel->setPixmap(QPixmap::fromImage(resultPic));
    emit hasGetDistance_Signal();
}


void ResultPic::on_label_drawAutoMeasureResult()
{
    cv::Mat tempM = resultPic_M;
    matPro = MatProcess(tempM);
    if (MeasurePattern == 0){
        //运行选区衍射（SAD）
        matPro.SAD();
    }
    else if (MeasurePattern == 1){
        //运行高分辨像(HRF)
        matPro.HRF();
    }
    else if (MeasurePattern == 2){
        //明场像(BF)
        matPro.BF();
    }
    else if (MeasurePattern == 3){
        //暗场像(DF)
        matPro.DF();
    }
    pointsDistance = matPro.distance;
    const uchar *pSrc = (const uchar *)tempM.data;
    int width = screenLabel->width();
    int height = screenLabel->height();
    resultPic = QImage(pSrc, width, height, tempM.step, QImage::Format_RGB888).rgbSwapped();
    screenLabel->setPixmap(QPixmap::fromImage(resultPic));
    tempM.release();
}

float ResultPic::getDistance()
{
    return pointsDistance;
}

void ResultPic::setDistance(const float &distance)
{
    this->pointsDistance = distance;
}

void ResultPic::setPic(const QImage &pic)
{
    editPicBtn->setEnabled(true);
    savePicBtn->setEnabled(true);
    this->resultPic = pic;
    screenLabel->setPixmap(QPixmap::fromImage(resultPic));
}

void ResultPic::setPic(const cv::Mat &pic)
{
    resultPic_M = pic;
}

void ResultPic::setMeasurePattern(const int &mode)
{
    MeasurePattern = mode;
}
