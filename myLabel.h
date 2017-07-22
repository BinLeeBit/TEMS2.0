#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>
#include <QPoint>
#include <QColor>
#include <QPaintEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    //explicit myLabel(QWidget *parent = 0);
    myLabel();
    ~myLabel();
    void paintEvent(QPaintEvent *event);
    int getLineSize();
private:
    QPoint lineStartPoint;          //画线起点
    QPoint lineEndPoint;            //画线终点
    QColor lineColor;               //线条颜色
    int lineSize;                  //5种线型
};

#endif // MYLABEL_H
