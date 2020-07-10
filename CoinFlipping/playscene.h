#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"

namespace Ui {
class PlayScene;
}

class PlayScene : public QMainWindow
{
    Q_OBJECT

public:
    bool isWon;
    int levelNum;
    int levelData[4][4];
    Coin * coins[4][4];

    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    ~PlayScene();
    void paintEvent(QPaintEvent *);

private:
    Ui::PlayScene *ui;

signals:
    void backBtnClicked();
};

#endif // PLAYSCENE_H
