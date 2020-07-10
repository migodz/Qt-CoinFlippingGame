#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

namespace Ui {
class ChooseLevelScene;
}

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

public:
    PlayScene * playScene = NULL;
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    ~ChooseLevelScene();

    void paintEvent(QPaintEvent *);

private:
    Ui::ChooseLevelScene *ui;

signals:
    void backBtnClicked();
};

#endif // CHOOSELEVELSCENE_H
