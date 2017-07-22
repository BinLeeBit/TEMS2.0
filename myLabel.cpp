#include "myLabel.h"
#include <QPen>
#include<QPainter>

myLabel::myLabel()
{

}

void paintEvent(QPaintEvent *event)
{

    QLabel::paintEvent(event);
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);

    //painter.drawLine(lineStartPoint,lineEndPoint);
}

int myLabel::getLineSize()
{
    return lineSize;
}
