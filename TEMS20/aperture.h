#ifndef APERTURE_H
#define APERTURE_H

//光阑处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

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

signals:

public slots:
};

#endif // APERTURE_H
