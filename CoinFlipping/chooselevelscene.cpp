#include "chooselevelscene.h"
#include "ui_chooselevelscene.h"
#include "myimgpushbutton.h"
#include "playscene.h"

#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QSound>
#include <QMessageBox>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseLevelScene)
{
    ui->setupUi(this);

    QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyImgPushButton * backBtn = new MyImgPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    backBtn->show();
    connect(backBtn, &MyImgPushButton::clicked, [=](){
        backSound->play();
        emit this->backBtnClicked();
    });

    //退出事件实现
    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    //关于事件实现
    connect(ui->actionAbout, &QAction::triggered, [=](){
        QMessageBox::about(this, "关于翻金币", "Code by 阿谜\nLanguage: C++ with Qt\n\n\t2020-07-09 ");
    });


    //关卡选择按钮生成
    for (int i = 0; i < 20; i++)
    {
        MyImgPushButton * tempBtn = new MyImgPushButton(":/res/LevelIcon.png");
        tempBtn->setParent(this);
        tempBtn->move(25+(i%4)*70, 130+(i/4)*70);
        tempBtn->show();

        //绑定按钮点击事件
        connect(tempBtn, &MyImgPushButton::clicked, [=](){
            chooseSound->play();
            tempBtn->jumpDown();
            tempBtn->jumpUp();
            QTimer::singleShot(300, [=](){
                this->hide();
                playScene = new PlayScene(i+1);
                playScene->setGeometry(this->geometry());
                playScene->show();

                //监听游戏窗口的返回按钮点击事件
                connect(playScene, &PlayScene::backBtnClicked, [=](){
                   playScene->hide();
                   setGeometry(playScene->geometry());
                   delete playScene;
                   playScene = NULL;
                   this->show();
                });
            });
        });

        //设置按钮上的数字标签
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(tempBtn->width(),tempBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        label->move(25 + (i%4)*70 , 130+ (i/4)*70);
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);  //鼠标事件穿透
        label->setFont(QFont("华文细黑",10));
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    //加载背景图
    if(!pix.load(":/res/OtherSceneBg.png"))
    {
        qDebug() << "加载失败";
        return;
    }
    painter.drawPixmap(0,0,pix);

    //加载标题图
    pix.load(":/res/Title.png");
    painter.drawPixmap(15, 50, pix.width()*0.5, pix.height()*0.5, pix);

}

ChooseLevelScene::~ChooseLevelScene()
{
    delete ui;
}
