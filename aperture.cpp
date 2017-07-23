#include "aperture.h"
#include <QHBoxLayout>
#include <sstream>
#include <QFileDialog>
#include <QMessageBox>

Aperture::Aperture(int idAperture,QWidget *parent) : QWidget(parent)
{
    //Label名称
    this->idAperture = idAperture;
    std::stringstream str;
    str << idAperture;
    screenName = "光阑";
    screenName.append(str.str().c_str());
    screenName += "处摄像机";
    screenLabel = new QLabel(screenName);
    screenLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    screenLabel->setAlignment(Qt::AlignCenter);
    screenLabel->setStyleSheet ("background-color: rgb(0,0,255);");
    openCamBtn = new QPushButton(tr("打开摄像机"));
    openCamBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    savePicBtn = new QPushButton(tr("保存"));
    savePicBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    savePicBtn->setEnabled(false);

    QHBoxLayout *botton = new QHBoxLayout();
    botton->setMargin(0);
    botton->addWidget(openCamBtn);
    botton->addWidget(savePicBtn);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(8);
    mainLayout->setSpacing(8);
    mainLayout->addWidget(screenLabel);
    mainLayout->addLayout(botton);
    //----------------------连接信号与槽------------------//
    connect(openCamBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_openCamBtn_clicked()));
    connect(savePicBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_savePicBtn_clicked()));
    //----------------------功能部分初始化----------------//
    idCamera = 0;   //默认打开本机
}

void Aperture::on_pushButton_openCamBtn_clicked()
{
    if(!ApertureCam->isOpen()){
        if(ApertureCam->OpenCamera()){
            openCamBtn->setText(tr("关闭摄像头"));
            ApertureCam->timer->start(33);
            savePicBtn->setEnabled(true);
        }
        else{
            screenLabel->setText(tr("摄像头打开失败"));
        }
    }
    else{
        ApertureCam->CloseCamera();
        ApertureCam->timer->stop();
        openCamBtn->setText(tr("打开摄像头"));
        screenLabel->setText(screenName);
        savePicBtn->setEnabled(false);
    }
}

void Aperture::on_pushButton_savePicBtn_clicked()
{
    QImage tempImage = camFram_QImage;
    QString pictureFileName = QFileDialog::getSaveFileName(this,
        tr("保存图片"),
        "",
        tr("*.png;; *.bmp;; *.jpg;; *.tif;; *.GIF")); //选择路径
    if (pictureFileName.isEmpty()){
        return;
    }
    else{
        if (!(tempImage.save(pictureFileName))){
            QMessageBox::information(this,
                tr("图片保存失败"),
                tr("图片保存失败"));
            return;
        }
    }
}

void Aperture::Cam_ReadFram()
{
    ApertureCam->capture>>camFram_Mat;
    const uchar *pSrc = (const uchar *)camFram_Mat.data;
    int width = screenLabel->width();
    int height = screenLabel->height();
    camFram_QImage = QImage(pSrc, width, height,camFram_Mat.step, QImage::Format_RGB888).rgbSwapped();//QImage::Format_BGR30
    screenLabel->setPixmap(QPixmap::fromImage(camFram_QImage));
}

void Aperture::Init(int idCamera)
{
    this->idCamera = idCamera;
    ApertureCam = new CameraOperate(idCamera);
    connect(ApertureCam->timer,SIGNAL(timeout()),this,SLOT(Cam_ReadFram()));
}
