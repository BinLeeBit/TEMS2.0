#ifndef RESULTPIC_H
#define RESULTPIC_H

//处理结果图片处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "editpic.h"

class ResultPic : public QWidget
{
    Q_OBJECT
public:
    explicit ResultPic(QWidget *parent = 0);
    //得到点的距离
    float getDistance();

private:
    QLabel *screenLabel;            //显示屏
    QPushButton *editPicBtn;        //编辑图片
    QPushButton *savePicBtn;        //保存结果图片

    QVBoxLayout *mainLayout;
    EditPic *editPicWidget;
    float pointsDistance;

signals:
    void hasGetDistance_Signal();
public slots:
    void on_pushButton_editPicBtn_clicked();
    void on_getDistance();
};

#endif // RESULTPIC_H
