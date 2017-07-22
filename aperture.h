#ifndef APERTURE_H
#define APERTURE_H

//光阑处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
//#include "CameraOperate.h"

class Aperture : public QWidget
{
    Q_OBJECT
public:
    explicit Aperture(QWidget *parent = 0);

private:
    QLabel *screenLabel;            //显示屏
    QPushButton *openCamBtn;        //打开相机
    QPushButton *savePicBtn;        //保存当前帧
    QVBoxLayout *mainLayout;
    //CameraOperate *ApertureCam;     //摄像机
signals:

public slots:
    //打开摄像机槽函数
    void on_pushButton_openCamBtn_clicked();

};

#endif // APERTURE_H
