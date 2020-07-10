#ifndef MYIMGPUSHBUTTON_H
#define MYIMGPUSHBUTTON_H

#include <QPushButton>

class MyImgPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyImgPushButton(QWidget *parent = nullptr);
    QString normalImgPath;
    QString pushedImgPath;
    MyImgPushButton(QString normalImgPath, QString pushedImgPath = "");
    void jumpUp();
    void jumpDown();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:

};

#endif // MYIMGPUSHBUTTON_H
