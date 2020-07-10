#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myimgpushbutton.h"
#include "chooselevelscene.h"

#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSound>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);

//    初始化选择关卡页面
    chooseScene = new ChooseLevelScene;

    //退出事件实现
    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    //关于事件实现
    connect(ui->actionAbout, &QAction::triggered, [=](){
        QMessageBox::about(this, "关于翻金币", "Code by 阿谜\nLanguage: C++ with Qt\n\n\t2020-07-09 ");
    });

//    开始按钮
    MyImgPushButton * startBtn = new MyImgPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5, this->height()*0.7);
    startBtn->show();
    connect(startBtn, &MyImgPushButton::clicked, [=](){
        startSound->play();
        //按钮弹跳
        startBtn->jumpDown();
        startBtn->jumpUp();

        //0.5秒后打开选择关卡页面
        QTimer::singleShot(500, this, [=](){
            this->hide();
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    //监听选择关卡窗口的返回按钮点击事件
    connect(chooseScene, &ChooseLevelScene::backBtnClicked, [=](){
       chooseScene->hide();
       setGeometry(chooseScene->geometry());
       this->show();
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(15, 60, pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

