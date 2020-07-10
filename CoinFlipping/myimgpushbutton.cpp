#include "myimgpushbutton.h"

#include<QDebug>
#include<QPropertyAnimation>

MyImgPushButton::MyImgPushButton(QString normalImgPath, QString pushedImgPath)
{
    this->normalImgPath = normalImgPath;
    this->pushedImgPath = pushedImgPath;
    QPixmap pix;
    if(!pix.load(normalImgPath))
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

}

//鼠标事件
void MyImgPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pushedImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pix;
        if(!pix.load(pushedImgPath))
        {
            qDebug() << pushedImgPath << "加载图片失败!";
        }

        this->setFixedSize( pix.width(), pix.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类执行按下事件
    QPushButton::mousePressEvent(e);
}

void MyImgPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pix;
        if(!pix.load(normalImgPath))
        {
            qDebug() << normalImgPath << "加载图片失败!";
        }

        this->setFixedSize( pix.width(), pix.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //交给父类执行按下事件
    QPushButton::mouseReleaseEvent(e);
}

void MyImgPushButton::jumpDown()
{
    //创建动画对象
    QPropertyAnimation * anima = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    anima->setDuration(200);
    //创建起始位置
    anima->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    anima->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    anima->start();
}

void MyImgPushButton::jumpUp()
{
    //创建动画对象
    QPropertyAnimation * anima = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    anima->setDuration(200);
    //创建起始位置
    anima->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    anima->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    anima->start();
}
