#ifndef SELECTANDRESULT_H
#define SELECTANDRESULT_H

//右侧区选择和结果区域
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QTimer>

class SelectAndResult : public QWidget
{
    Q_OBJECT
public:
    explicit SelectAndResult(QWidget *parent = 0);
    //设置距离
    void setDistance(float distance);
private:
    QLabel *motorCtrlLabel;         //电机控制
    QPushButton *motorCtrlBtn;
    QLabel *measureMethodLabel;     //测量方式
    QPushButton *measureMethodBtn;
    QLabel *dateLabel;              //当前时间
    QLabel *displayDateLabel;
    QLabel *distanceLabel;          //测量结果显示区
    QTextBrowser *distanceTextBrowser;
    QVBoxLayout *mainLayout;

    QTimer *timer;                  //计时器
    float pointsDistance;           //点间距离
signals:

public slots:
    void timerUpdate();             //时间更新
    void on_pushButton_motorCtrlBtn_clicked();
};

#endif // SELECTANDRESULT_H
