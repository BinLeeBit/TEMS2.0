#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QPoint>
#include <QColor>
#include <QPaintEvent>

class myLabel : public QLabel
{
    //Q_OBJECT
public:
    //explicit myLabel(QWidget *parent = 0);
    myLabel();
    //~myLabel();
    //绘制线条
    virtual void paintEvent(QPaintEvent *event) override;
    //鼠标按下
    void mousePressEvent(QMouseEvent *e);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *e);
    //鼠标抬起
    void mouseReleaseEvent(QMouseEvent *e);
    //设置所画线条属性
    void setLineColor(const QColor lineColor);
    void setLineSize(const int lineSize);
    //得到画线的起点和终点
    QPoint getStartPoint();
    QPoint getEndPoint();

    void clear();

private:
    QPoint lineStartPoint;          //画线起点
    QPoint lineEndPoint;            //画线终点
    QColor lineColor;               //线条颜色
    int lineSize;                  //5种线型
    bool isPressed;
};

#endif // MYLABEL_H
