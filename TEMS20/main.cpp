#include "tems.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("AR PL KaitiM GB", 11);
    a.setFont(font);

    /* no use
    //QSplitter *mainSplitter = new QSplitter(Qt::Horizontal,0);
    //mainSplitter->setOpaqueResize(true);//设置窗口可拖拽
    //mainSplitter->setStretchFactor(0,1);//设置控件可拖拽
    tems *w = new tems(mainSplitter);
    mainSplitter->setMinimumSize(mainSplitter->minimumSize());
    mainSplitter->setMaximumSize(mainSplitter->maximumSize());
    mainSplitter->show();
    */

    tems *w = new tems(0);
    w->showMaximized();     //开始最大化显示
    //w->show();

    return a.exec();
}
