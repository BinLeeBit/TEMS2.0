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
    confirmBtn->setEnabled(false);

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

    //-----------------连接信号与槽----------------//
    connect(openCamBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_openCamBtn_clicked()));
    connect(confirmBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_confirmBtn_clicked()));

    //-----------------初始化---------------------//
    idCamera = 0;
}

void OpticalScreen::on_pushButton_openCamBtn_clicked()
{

    if(!OpticalScreenCam->isOpen()){
        if(OpticalScreenCam->OpenCamera()){
            openCamBtn->setText(tr("关闭摄像头"));
            OpticalScreenCam->timer->start(33);
            confirmBtn->setEnabled(true);
        }
        else{
            screenLabel->setText(tr("摄像头打开失败"));
        }
    }
    else{
        OpticalScreenCam->CloseCamera();
        OpticalScreenCam->timer->stop();
        openCamBtn->setText(tr("打开摄像头"));
        screenLabel->setText(tr("光屏处摄像机"));
        confirmBtn->setEnabled(false);
    }
}

void OpticalScreen::on_pushButton_confirmBtn_clicked()
{
    emit hasConfirm_Signal();
}

void OpticalScreen::Cam_ReadFram()
{
    OpticalScreenCam->capture>>camFram_Mat;
    const uchar *pSrc = (const uchar *)camFram_Mat.data;
    int width = screenLabel->width();
    int height = screenLabel->height();
    camFram_QImage = QImage(pSrc, width, height,camFram_Mat.step, QImage::Format_RGB888).rgbSwapped();//QImage::Format_BGR30
    screenLabel->setPixmap(QPixmap::fromImage(camFram_QImage));
}

void OpticalScreen::Init(int idCamera)
{
    this->idCamera = idCamera;
    OpticalScreenCam = new CameraOperate(idCamera);
    connect(OpticalScreenCam->timer,SIGNAL(timeout()),this,SLOT(Cam_ReadFram()));
}

QImage OpticalScreen::getConfirmedPic()
{
    return camFram_QImage;
}

cv::Mat OpticalScreen::getConfirmedPic_M()
{
    return camFram_Mat;
}

int OpticalScreen::getMeasurePattern()
{
    return patternComboBox->currentIndex();
}
