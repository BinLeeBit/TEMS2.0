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
    //绘制线条
    void paintEvent();
    //鼠标按下
    void mousePressEvent(QMouseEvent *e);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *e);
    //鼠标抬起
    void mouseReleaseEvent(QMouseEvent *e);
    //在picLabel绘制
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QLabel *picLabel;               //测量图片
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

private slots:
    void showColor();
    void on_pushButton_revokeBtn_clicked();
    void on_pushButton_cancelBtn_clicked();
    //void on_pushButton_confirmBtn_clicked();
};

#endif // EDITPIC_H
