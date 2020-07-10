#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    QTimer * timer1;
    QTimer * timer2;
    bool isFrontSide;
    bool isAnimating = false;
    bool isWon = false;
    int posX, posY;
    int min = 1;
    int max = 8;

    //explicit Coin(QWidget *parent = nullptr);
    Coin(QString imgPath);
    void filpSide();
    void mousePressEvent(QMouseEvent *);

signals:

};

#endif // COIN_H
