#ifndef RESULTPIC_H
#define RESULTPIC_H

//处理结果图片处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "editpic.h"
#include "MatProcess.h"

class ResultPic : public QWidget
{
    Q_OBJECT
public:
    explicit ResultPic(QWidget *parent = 0);
    //得到点的距离
    float getDistance();
    //设置点的距离
    void setDistance(const float &distance = 0);
    //设置处理的图像
    void setPic(const QImage &pic);
    void setPic(const cv::Mat &pic);
    //设置测量模式
    void setMeasurePattern(const int &mode);

private:
    QLabel *screenLabel;            //显示屏
    QPushButton *editPicBtn;        //编辑图片
    QPushButton *savePicBtn;        //保存结果图片

    QVBoxLayout *mainLayout;
    EditPic *editPicWidget;
    float pointsDistance;           //距离
    QImage resultPic;               //结果图
    cv::Mat resultPic_M;
    int MeasurePattern;             //测量模式
    MatProcess matPro;              //图像自动处理

signals:
    void hasGetDistance_Signal();
    //采取手动测量的信号
    void ManualWayInfo_Singal();
public slots:
    void on_pushButton_editPicBtn_clicked();
    void on_getDistance();
    //在原图上绘制测量结果
    void on_label_drawAutoMeasureResult();
};

#endif // RESULTPIC_H
