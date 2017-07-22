#ifndef TEMS_H
#define TEMS_H

#include <QDialog>
#include <QPushButton>
#include "aperture.h"
#include "opticalscreen.h"
#include "resultpic.h"
#include "SelectAndResult.h"
#include <QGridLayout>
#include <QVBoxLayout>

class tems : public QWidget
{
    Q_OBJECT

public:
    tems(QWidget *parent = 0);
    ~tems();

    Aperture *aperture1;         //光阑1
    Aperture *aperture2;         //光阑2
    OpticalScreen *opticalscreen;//光屏
    ResultPic *resultpic;        //处理结果图片
    SelectAndResult *selectandresult;   //选择和结果显示区

    //布局
    /*QVBoxLayout *leftLayout;
    QVBoxLayout *midLayout;
    QVBoxLayout *rightLayout;
    */
    QGridLayout *mainLayout;

signals:

public slots:
    void on_Widget_resultpic_getDistance();
};

#endif // TEMS_H
