#include "myLabel.h"
#include <QPen>
#include<QPainter>

myLabel::myLabel()
{
    this->lineStartPoint = QPoint(0,0);
    this->lineEndPoint = QPoint(0,0);
    this->lineColor = QColor(Qt::black);
    this->lineSize = 3;
}

//绘制线条
void myLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(lineSize);
    painter.setPen(pen);
    painter.drawLine(lineStartPoint,lineEndPoint);
}

//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *e)
{
    lineStartPoint = e->pos();
    lineEndPoint = e->pos();
    //在图片上绘制
    isPressed = true;
}

//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        lineEndPoint=e->pos();
        update();
    }
}

//鼠标抬起
void myLabel::mouseReleaseEvent(QMouseEvent *e)
{
    isPressed=false;
    update();
}

void myLabel::setLineColor(const QColor lineColor)
{
    this->lineColor = lineColor;
}

void myLabel::setLineSize(const int lineSize)
{
    this->lineSize = lineSize;
}

QPoint myLabel::getStartPoint()
{
    return lineStartPoint;
}

QPoint myLabel::getEndPoint()
{
    return lineEndPoint;
}

void myLabel::clear()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    update();
}
