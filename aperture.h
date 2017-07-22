#ifndef APERTURE_H
#define APERTURE_H

//光阑处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "CameraOperate.h"

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
    CameraOperate cam;
signals:

public slots:
};

#endif // APERTURE_H
