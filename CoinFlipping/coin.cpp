#include "coin.h"
#include <QDebug>
#include <QWaitCondition>

Coin::Coin(QString imgPath)
{
    QPixmap pix;
    if(!pix.load(imgPath))
    {
        qDebug() << "图片加载失败";
        return;
    }
    //设置按钮大小为图片大小
    setFixedSize(pix.width(), pix.height());

    //设置按钮为不规则样式
    setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    setIcon(QIcon(pix));
    setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻转的信号槽
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
            this->min = 1;
            timer1->stop();
            isAnimating = false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pixmap;
        QString str = QString(":/res/Coin000%1.png").arg((this->max)-- );
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
            this->max = 8;
            timer2->stop();
            isAnimating = false;
        }
    });


}

void Coin::filpSide()
{
//    qDebug()<<"翻转了:"<<posX<<","<<posY;
    if(isFrontSide)
    {
        timer1->start(30);
    }
    else
    {
        timer2->start(30);
    }
    isAnimating = true;
    isFrontSide = !isFrontSide;
}

void Coin::mousePressEvent(QMouseEvent * e)
{
    if(isAnimating || isWon)
        return;
    return QPushButton::mousePressEvent(e);
}
