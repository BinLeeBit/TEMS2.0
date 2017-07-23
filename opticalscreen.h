#ifndef OPTICALSCREEN_H
#define OPTICALSCREEN_H

//光屏处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <opencv2/opencv.hpp>
#include "CameraOperate.h"
#include <QImage>

class OpticalScreen : public QWidget
{
    Q_OBJECT
public:
    explicit OpticalScreen(QWidget *parent = 0);
    //初始化光屏和摄像机编号
    void Init(int idCamera = 0);
    //获得已经确定的图像
    QImage getConfirmedPic();
    cv::Mat getConfirmedPic_M();
    //获得测量模式
    int getMeasurePattern();
private:
    QLabel *screenLabel;            //显示屏
    QPushButton *openCamBtn;        //打开相机
    QLabel *workPatternLabel;       //工作模式
    QComboBox *patternComboBox;     //选择工作模式
    QPushButton *confirmBtn;        //选择当前区域图片为测量样本
    QVBoxLayout *mainLayout;
    CameraOperate *OpticalScreenCam;//摄像机
    int idCamera;                   //摄像机的编号
    cv::Mat camFram_Mat;            //摄像机处帧图像
    QImage camFram_QImage;

signals:
    //已经确认选择当前图片
    void hasConfirm_Signal();

public slots:
    void on_pushButton_openCamBtn_clicked();
    void on_pushButton_confirmBtn_clicked();
    void Cam_ReadFram();
};

#endif // OPTICALSCREEN_H
