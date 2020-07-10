#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ChooseLevelScene * chooseScene = NULL;

    //重写paintEvent
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
