#include "playscene.h"
#include "ui_playscene.h"

#include "myimgpushbutton.h"
#include "dataconfig.h"
#include "coin.h"
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QPropertyAnimation>
#include <QSound>
#include <QMessageBox>


PlayScene::PlayScene(int levelNum) :
    ui(new Ui::PlayScene)
{
    ui->setupUi(this);
    this->levelNum = levelNum;

    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);

    //退出事件
    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    //关于事件
    connect(ui->actionAbout, &QAction::triggered, [=](){
        QMessageBox::about(this, "关于翻金币", "Code by 阿谜\nLanguage: C++ with Qt\n\n\t2020-07-09 ");
    });

    //返回按钮
    MyImgPushButton * backBtn = new MyImgPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    backBtn->show();
    connect(backBtn, &MyImgPushButton::clicked, [=](){
        backSound->play();
        QTimer::singleShot(300, [=](){
            emit this->backBtnClicked();
        });
    });

    //显示关卡标签
    ui->label->setText("Level："+QString::number(levelNum));

    //调整胜利提示标签位置
    ui->congraLabel->move( (this->width() - 241)*0.5 , -83);

    //初始化二维数组
    dataConfig config;

    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50,200+j*50);

            //金币对象
            QString img;
            if(config.mData[this->levelNum][i][j] == 1)
                img = ":/res/Coin0001.png";
            else
                img = ":/res/Coin0008.png";
            Coin * coin = new Coin(img);
            coin->setParent(this);
            coin->move(59 + i*50,204+j*50);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->isFrontSide = config.mData[this->levelNum][i][j]; //记录正反标志
            coins[i][j] = coin;

            //金币被点击
            connect(coin,&Coin::clicked,[=](){
                flipSound->play();
                coin->filpSide();

                //翻转周围金币
                QTimer::singleShot(300, this,[=](){
                    if(coin->posX>0)
                        coins[coin->posX-1][coin->posY]->filpSide();
                    if(coin->posX<3)
                        coins[coin->posX+1][coin->posY]->filpSide();
                    if(coin->posY>0)
                        coins[coin->posX][coin->posY-1]->filpSide();
                    if(coin->posY<3)
                        coins[coin->posX][coin->posY+1]->filpSide();

                    //判断是否胜利
                    this->isWon = true;
                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                            if( coins[i][j]->isFrontSide == false)
                            {
                                this->isWon = false;
                                break;
                            }
                        }
                    }
                    if(isWon)
                    {
                        winSound->play();

                        //胜利动画
                        QPropertyAnimation * anima =  new QPropertyAnimation(ui->congraLabel,"geometry");
                        anima->setDuration(1000);
                        anima->setStartValue(QRect(ui->congraLabel->x(),ui->congraLabel->y(),ui->congraLabel->width(),ui->congraLabel->height()));
                        anima->setEndValue(QRect(ui->congraLabel->x(),ui->congraLabel->y()+114,ui->congraLabel->width(),ui->congraLabel->height()));
                        anima->setEasingCurve(QEasingCurve::OutBounce);
                        anima->start();

                        //把金币设置为胜利状态
                        for(int i = 0 ; i < 4;i++)
                            for(int j = 0 ; j < 4; j++)
                                coins[i][j]->isWon = true;
                    }
                });
            });


        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, pix);
    pix.load(":/res/Title.png");
    painter.drawPixmap(15, 50, pix.width()*0.5, pix.height()*0.5, pix);
}

PlayScene::~PlayScene()
{
    delete ui;
}
