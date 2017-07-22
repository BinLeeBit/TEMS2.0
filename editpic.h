#ifndef EDITPIC_H
#define EDITPIC_H

//手动测量图片编辑
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QColorDialog>
#include <QPoint>
#include <QLine>
#include <QMouseEvent>
#include "myLabel.h"

#define MARGIN_EDITPIC 40
#define SPACING_EDITPIC 20

class EditPic : public QWidget
{
    Q_OBJECT
public:
    explicit EditPic(QWidget *parent = 0);
    ~EditPic();

    //得到线条粗细
    int getLineSize();
    //得到线条颜色
    QColor getLineColor();
    //得到线条起点
    QPoint getLineStartPoint();
    //得到线条终点
    QPoint getLineEndPoint();
    //得到线条长度
    float getLineLenth();

private:
    myLabel *picLabel;               //测量图片
    QPushButton *colorEditBtn;      //线条颜色
    QComboBox *lineSizeComboBox;    //线条粗细
    QPushButton *confirmBtn;        //确认按钮
    QPushButton *cancelBtn;         //取消按钮
    QPushButton *revokeBtn;         //撤销按钮
    QGridLayout *mainLayout;
    QColor lineColor;               //线条颜色
    int *lineSize;                  //5种线型

    QPoint lineStartPoint;          //画线起点
    QPoint lineEndPoint;            //画线终点
    bool isPressed = false;                 //鼠标是否已经按下
signals:
    //发送点击了确定的信号
    void confirmBtn_Signal();
public slots:
    void on_pushButton_colorEditBtn_clicked();
    void on_pushButton_revokeBtn_clicked();
    void on_pushButton_cancelBtn_clicked();
    void on_pushButton_confirmBtn_clicked();
    void on_comboBox_lineSizeComboBox_indexChanged();
};

#endif // EDITPIC_H
