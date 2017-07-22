#ifndef OPTICALSCREEN_H
#define OPTICALSCREEN_H

//光屏处Widget
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>

class OpticalScreen : public QWidget
{
    Q_OBJECT
public:
    explicit OpticalScreen(QWidget *parent = 0);

private:
    QLabel *screenLabel;            //显示屏
    QPushButton *openCamBtn;        //打开相机
    QLabel *workPatternLabel;       //工作模式
    QComboBox *patternComboBox;     //选择工作模式
    QPushButton *confirmBtn;        //选择当前区域图片为测量样本
    QVBoxLayout *mainLayout;

signals:

public slots:
};

#endif // OPTICALSCREEN_H
