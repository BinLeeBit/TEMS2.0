#ifndef APERTURE_H
#define APERTURE_H

//光阑处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "CameraOperate.h"

class Aperture : public QWidget
{
    Q_OBJECT
public:
    explicit Aperture(int idAperture, QWidget *parent = 0);
    //初始化光屏和摄像机编号
    void Init(int idCamera = 0);

private:
    QLabel *screenLabel;            //显示屏
    QPushButton *openCamBtn;        //打开相机
    QPushButton *savePicBtn;        //保存当前帧
    QVBoxLayout *mainLayout;
    CameraOperate *ApertureCam;     //摄像机
    int idCamera;                   //摄像机的编号
    int idAperture;                 //光屏编号
    QString screenName;             //光屏名称
    cv::Mat camFram_Mat;            //摄像机处帧图像
    QImage camFram_QImage;
signals:

public slots:
    //打开摄像机槽函数
    void on_pushButton_openCamBtn_clicked();
    void on_pushButton_savePicBtn_clicked();
    void Cam_ReadFram();

};

#endif // APERTURE_H
