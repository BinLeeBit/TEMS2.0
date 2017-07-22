#include "editpic.h"
#include <QtMath>
#include <QPen>
#include <QPainter>

EditPic::EditPic(QWidget *parent) : QWidget(parent)
{
    //------------------界面绘制-----------------//
    colorEditBtn = new QPushButton();
    int h = colorEditBtn->height();
    colorEditBtn->resize(h,h);
    colorEditBtn->setStyleSheet("background-color: rgb(0,0,0);");
    lineSizeComboBox = new QComboBox();
    lineSizeComboBox->insertItem(2,tr("适中"));
    lineSizeComboBox->insertItem(0,tr("极细"));
    lineSizeComboBox->insertItem(1,tr("较细"));
    lineSizeComboBox->insertItem(3,tr("较粗"));
    lineSizeComboBox->insertItem(4,tr("极粗"));
    revokeBtn = new QPushButton(tr("撤销"));
    revokeBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    cancelBtn = new QPushButton(tr("取消"));
    cancelBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    confirmBtn = new QPushButton(tr("确定"));
    confirmBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    picLabel = new QLabel(tr("手动测量图片"));
    picLabel->setAlignment(Qt::AlignCenter);
    picLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    picLabel->setStyleSheet("background-color: rgb(0,0,255);");

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(SPACING_EDITPIC);
    topLayout->addWidget(colorEditBtn);
    topLayout->addWidget(lineSizeComboBox);
    topLayout->addWidget(revokeBtn);
    topLayout->addWidget(cancelBtn);
    topLayout->addWidget(confirmBtn);
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(MARGIN_EDITPIC);
    mainLayout->setSpacing(SPACING_EDITPIC);
    mainLayout->addLayout(topLayout,0,0);
    mainLayout->addWidget(picLabel,1,0);

    //-----------------链接信号和槽-----------------//
    connect(colorEditBtn,SIGNAL(clicked(bool)),this,SLOT(showColor()));
    connect(revokeBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_revokeBtn_clicked()));
    connect(cancelBtn,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_cancelBtn_clicked()));
    //----------------功能部分初始化----------------//
    lineSize = new int[5];
    for(unsigned int i =0;i<5;i++){
        lineSize[i]=i+1;
    }
    lineColor = Qt::black;

}

EditPic::~EditPic()
{
    EditPic::close();
}

void EditPic::showColor()
{
    lineColor = QColorDialog::getColor(Qt::blue);
    if(lineColor.isValid()){
        int r = lineColor.red();
        int g = lineColor.green();
        int b = lineColor.blue();
        QString rgb("background-color: rgb("+QString::number(r,10)+","
                +QString::number(g,10)+","+QString::number(b,10)+");");
        colorEditBtn->setStyleSheet(rgb);
    }
}

void EditPic::on_pushButton_revokeBtn_clicked()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
}

void EditPic::on_pushButton_cancelBtn_clicked()
{
    lineStartPoint = QPoint(0,0);
    lineEndPoint = QPoint(0,0);
    this->close();
}

//得到线条粗细
int EditPic::getLineSize()
{
    return lineSize[lineSizeComboBox->currentIndex()];
}

//得到线条颜色
QColor EditPic::getLineColor()
{
    return lineColor;
}

//得到线条起点
QPoint EditPic::getLineStartPoint()
{
    return lineStartPoint;
}

//得到线条终点
QPoint EditPic::getLineEndPoint()
{
    return lineEndPoint;
}

//得到线条长度
float EditPic::getLineLenth()
{
    return sqrtf(powf(lineStartPoint.x()-lineEndPoint.x(),2.0f)+
                 powf(lineStartPoint.y()-lineEndPoint.y(),2.0f));
}

bool EditPic::eventFilter(QObject *watched, QEvent *event)
{
    if(watched ==picLabel && event->type() == QEvent::Paint){
        paintEvent();
    }
    return QWidget::eventFilter(watched,event);
}

//绘制线条
void EditPic::paintEvent()
{
    QPainter painter(picLabel);
    QPen pen;
    pen.setColor(lineColor);
    pen.setWidth(lineSize[lineSizeComboBox->currentIndex()]);
    painter.setPen(pen);
    painter.drawLine(lineStartPoint,lineEndPoint);
}

//鼠标按下
void EditPic::mousePressEvent(QMouseEvent *e)
{
    lineStartPoint = e->pos();
    lineEndPoint = e->pos();
    //在图片上绘制
    if(lineStartPoint.x()>(picLabel->x()+picLabel->width())||lineStartPoint.x()<picLabel->x()||
            lineStartPoint.y()>(picLabel->y()+picLabel->height())||lineStartPoint.y()<picLabel->y()){
        isPressed = false;
        lineStartPoint = QPoint(0,0);
        lineEndPoint = QPoint(0,0);
    }
    else{
        isPressed = true;
    }
}

//鼠标移动
void EditPic::mouseMoveEvent(QMouseEvent *e)
{
    if(isPressed)
    {
        lineEndPoint=e->pos();
        update();
    }
}

//鼠标抬起
void EditPic::mouseReleaseEvent(QMouseEvent *e)
{
    isPressed=false;
    if(e->pos().x()>(picLabel->x()+picLabel->width())||e->pos().x()<picLabel->x()||
            e->pos().y()>(picLabel->y()+picLabel->height())||e->pos().y()<picLabel->y()){
        lineStartPoint = QPoint(0,0);
        lineEndPoint = QPoint(0,0);
    }
    update();
}
