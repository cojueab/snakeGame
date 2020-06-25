#include "windowgame.h"
#include <QColorDialog>
#include <QDebug>
#include <QTimer>
#include <QBrush>
#include <QKeyEvent>
#include <QMessageBox>
#include <QApplication>
#include <math.h>
#include <QTime>
#include <QSound>
#include <QLineEdit>
#include <QInputDialog>
#include <QtSql/QSql>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>


windowGame::windowGame(QWidget *parent,QColor windowColor,int hard,int colorSnake,bool intellect)
    : QWidget(parent)
{
    course = new bool[4];
    menu=new Menu();
    score=0;
   player=new QSound(":/images/3.wav");
    timer = new QTimer(this);
    if(hard==1){
        time=250;
    }
    else{
        if(hard==0){
            time=500;
        }
        else{
            time=100;
        }
    }
    _colorSnake=colorSnake;
    _intellect=intellect;
    QString colorString="background-color:"+windowColor.name()+";color:black;";
    this->setStyleSheet(colorString);
    start();
    y_shift=-20;
    x_shift=0;
    //
    snake=new Snake();
    pear = new food();
    pear->skill=0;
    apple = new food();
    apple->skill=1;
    banan = new food();
    banan->skill=2;

    portal=new Portal();

    lets=new obstacle();
    while(compareToLets(pear->getPoint(0).x,pear->getPoint(0).y)){
        pear->move();
    }
    while(compareToLets(apple->getPoint(0).x,apple->getPoint(0).y)){
        apple->move();
    }
    while(compareToLets(banan->getPoint(0).x,banan->getPoint(0).y)){
        banan->move();
    }
}

windowGame::~windowGame()
{

}


void windowGame::start(){
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(time);
}

void windowGame::paintEvent(QPaintEvent *event)
{
    //вызов перерисовки
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //функция расчитывает и затем рисует змейку и синие яблоки
    //Snake->animate(&painter, event, wi, he, snake_color);
    paintSnake();
    paintFood();
    paintObstacle();
    paintPortal();
    painter.end();
}


void windowGame::fCourse()
{
    for(int i = 0; i < 4; i++)
        course[i] = true;
    int size=snake->Counts();
    for(int i = 0; i < size; i++)
    {
        if(snake->getPoint(0).x == snake->getPoint(i).x && snake->getPoint(0).y - snake->getPoint(i).y == 20)
            course[1] = false;
        if(snake->getPoint(0).x == snake->getPoint(i).x && snake->getPoint(0).y - snake->getPoint(i).y == -20)
            course[3] = false;
        if(snake->getPoint(0).y == snake->getPoint(i).y && snake->getPoint(0).x - snake->getPoint(i).x == 20)
            course[0] = false;
        if(snake->getPoint(0).y == snake->getPoint(i).y && snake->getPoint(0).x - snake->getPoint(i).x == -20)
            course[2] = false;
    }
    size=lets->Counts();
    for(int i = 0; i < size; i++)
    {
        if(lets->getPoint(0).x == lets->getPoint(i).x && lets->getPoint(0).y - lets->getPoint(i).y == 20)
            course[1] = false;
        if(lets->getPoint(0).x == lets->getPoint(i).x && lets->getPoint(0).y - lets->getPoint(i).y == -20)
            course[3] = false;
        if(lets->getPoint(0).y == lets->getPoint(i).y && lets->getPoint(0).x - lets->getPoint(i).x == 20)
            course[0] = false;
        if(lets->getPoint(0).y == lets->getPoint(i).y && lets->getPoint(0).x - lets->getPoint(i).x == -20)
            course[2] = false;

    }

}

void windowGame::paintSnake(){
    timeToTime++;
    if(timeToTime==20 && time>5){
        time=time-5;
        timeToTime=0;
    }
    int size=snake->Counts();
    if(compare(snake->getPoint(0).x,snake->getPoint(0).y,portal->getPoint(0).x,portal->getPoint(0).y)){
        snake->changeXY(portal->getPoint(1).x,portal->getPoint(1).y,snake->Counts()-1);
        snake->moveEl(snake->Counts()-1,0);

    }
    else{
        if(compare(snake->getPoint(0).x,snake->getPoint(0).y,portal->getPoint(1).x,portal->getPoint(1).y)){
            snake->changeXY(portal->getPoint(0).x,portal->getPoint(0).y,snake->Counts()-1);
            snake->moveEl(snake->Counts()-1,0);
        }
    }
    if(_intellect) // Интеллект. Направление к яблоку.
    {
        int sPear=10000,sApple=10000,sBanan=10000;
            int number;
            if(pear->visibleFood){
                sPear=sqrt(pow((snake->getPoint(0).x-pear->getPoint(0).x),2)+pow((snake->getPoint(0).y-pear->getPoint(0).y),2));
            }
            if(apple->visibleFood){
                sApple=sqrt(pow((snake->getPoint(0).x-apple->getPoint(0).x),2)+pow((snake->getPoint(0).y-apple->getPoint(0).y),2));
            }
            if(banan->visibleFood){
                sBanan=sqrt(pow((snake->getPoint(0).x-banan->getPoint(0).x),2)+pow((snake->getPoint(0).y-banan->getPoint(0).y),2));
            }
            if(sPear<sApple){
                if(sPear<sBanan){
                    number=0;
                }
                else{
                    number=2;
                }
            }
            else{
                if(sApple<sBanan){
                    number=1;
                }
                else{
                    number=2;
                }
            }

            if(number==0){
                if(abs(snake->getPoint(0).x-pear->getPoint(0).x) > abs(snake->getPoint(0).y-pear->getPoint(0).y)){
                    int new_x;
                    if(snake->getPoint(0).x-pear->getPoint(0).x>0){
                        new_x=20;
                        y_shift=0;
                    }
                    else{
                        new_x=-20;
                        y_shift=0;
                    }
                    if(new_x!=0-x_shift){
                        x_shift=new_x;
                    }
                }
                else{
                    int new_y;
                    if(snake->getPoint(0).y-pear->getPoint(0).y>0){
                        x_shift=0;
                        new_y=20;
                    }
                    else{
                        x_shift=0;
                        new_y=-20;
                    }
                    if(new_y!=0-y_shift){
                        y_shift=new_y;
                    }
                }
            }
            if(number==1){
                if(abs(snake->getPoint(0).x-apple->getPoint(0).x) > abs(snake->getPoint(0).y-apple->getPoint(0).y)){
                    int new_x;
                    if(snake->getPoint(0).x-apple->getPoint(0).x>0){
                        new_x=20;
                        y_shift=0;
                    }
                    else{
                        new_x=-20;
                        y_shift=0;
                    }
                    if(new_x!=0-x_shift){
                        x_shift=new_x;
                    }
                }
                else{
                    int new_y;
                    if(snake->getPoint(0).y-apple->getPoint(0).y>0){
                        x_shift=0;
                        new_y=20;
                    }
                    else{
                        x_shift=0;
                        new_y=-20;
                    }
                    if(new_y!=0-y_shift){
                        y_shift=new_y;
                    }
                }
            }
            if(number==2){
                if(abs(snake->getPoint(0).x-banan->getPoint(0).x) > abs(snake->getPoint(0).y-banan->getPoint(0).y)){
                    int new_x;
                    if(snake->getPoint(0).x-banan->getPoint(0).x>0){
                        new_x=20;
                        y_shift=0;
                    }
                    else{
                        new_x=-20;
                        y_shift=0;
                    }
                    if(new_x!=0-x_shift){
                        x_shift=new_x;
                    }
                }
                else{
                    int new_y;
                    if(snake->getPoint(0).y-banan->getPoint(0).y>0){
                        x_shift=0;
                        new_y=20;
                    }
                    else{
                        x_shift=0;
                        new_y=-20;
                    }
                    if(new_y!=0-y_shift){
                        y_shift=new_y;
                    }
                }
            }
    }
    snake->move(x_shift,y_shift);

    if(pear->visibleFood){
        if(compare(snake->getPoint(0).x,snake->getPoint(0).y,pear->getPoint(0).x,pear->getPoint(0).y)){
            pear->visibleFood=false;
            snake->insert(x_shift,y_shift);
            snake->setSkill(pear->skill);
            timer->setInterval(time);
            player->play();
            score++;
        }
    }
    if(apple->visibleFood){
        if(compare(snake->getPoint(0).x,snake->getPoint(0).y,apple->getPoint(0).x,apple->getPoint(0).y)){
            apple->visibleFood=false;
            snake->insert(x_shift,y_shift);
            snake->setSkill(apple->skill);
            timer->setInterval(time*2);
            player->play();
             score++;
        }
    }
    if(banan->visibleFood){
        if(compare(snake->getPoint(0).x,snake->getPoint(0).y,banan->getPoint(0).x,banan->getPoint(0).y)){
            banan->visibleFood=false;
            snake->insert(x_shift,y_shift);
            snake->setSkill(banan->skill);
            timer->setInterval(time/2);
            player->play();
             score++;
        }
    }
    if(_colorSnake==0){
        for(int i=0;i<size;++i){
            if(i > 0 && i < size - 1){//Текстуры змейки кроме головы и хвоста
                QPixmap snake_px1;
                if ((snake->getPoint(i-1).y < snake->getPoint(i).y && snake->getPoint(i).x > snake->getPoint(i+1).x) ||         //Угловые части
                        (snake->getPoint(i+1).y < snake->getPoint(i).y && snake->getPoint(i-1).x < snake->getPoint(i).x))
                    snake_px1.load(":/images/Angle_lu.png");

                else if ((snake->getPoint(i+1).y < snake->getPoint(i).y && snake->getPoint(i).x < snake->getPoint(i-1).x) ||
                        (snake->getPoint(i-1).y < snake->getPoint(i).y && snake->getPoint(i+1).x > snake->getPoint(i).x))
                    snake_px1.load(":/images/Angle_ur.png");

                else if ((snake->getPoint(i-1).y > snake->getPoint(i).y && snake->getPoint(i).x < snake->getPoint(i+1).x) ||
                        (snake->getPoint(i+1).y > snake->getPoint(i).y && snake->getPoint(i-1).x > snake->getPoint(i).x))
                    snake_px1.load(":/images/Angle_rd.png");

                else if ((snake->getPoint(i+1).y > snake->getPoint(i).y && snake->getPoint(i).x > snake->getPoint(i-1).x) ||
                        (snake->getPoint(i-1).y > snake->getPoint(i).y && snake->getPoint(i+1).x < snake->getPoint(i).x))
                    snake_px1.load(":/images/Angle_dl.png");

                else if (snake->getPoint(i).x == snake->getPoint(i-1).x)                                                        //Прямые части
                    snake_px1.load(":/images/Straight_ver.png");
                else if (snake->getPoint(i).y == snake->getPoint(i-1).y)
                    snake_px1.load(":/images/Straight_hor.png");

                painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, snake_px1);

            }
            else if (i == 0){
                QPixmap snake_px;

                if (x_shift == 0 && y_shift == -20)                               //Текстуры головы
                    snake_px.load(":/images/Head_down.png");
                else if (x_shift == 0 && y_shift == 20)
                    snake_px.load(":/images/Head_up.png");
                else if (x_shift == 20 && y_shift == 0)
                    snake_px.load(":/images/Head_left.png");
                else if (x_shift == -20 && y_shift == 0)
                    snake_px.load(":/images/Head_right.png");

                painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, snake_px);
            }
            else if (i == size - 1){                                                  //Текстуры хвоста
                QPixmap tail_px;

                if (snake->getPoint(i-1).y < snake->getPoint(i).y)
                    tail_px.load(":/images/Tail_u.png");
                if (snake->getPoint(i-1).y > snake->getPoint(i).y)
                    tail_px.load(":/images/Tail_d.png");
                if (snake->getPoint(i-1).x > snake->getPoint(i).x)
                    tail_px.load(":/images/Tail_r.png");
                if (snake->getPoint(i-1).x < snake->getPoint(i).x)
                    tail_px.load(":/images/Tail_l.png");

                painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, tail_px);

            }
        }
    }
    else{
        if(_colorSnake==1){
            for(int i=0;i<size;++i){
                if(i > 0 && i < size - 1){//Текстуры змейки кроме головы и хвоста
                    QPixmap snake_px1;
                    if ((snake->getPoint(i-1).y < snake->getPoint(i).y && snake->getPoint(i).x > snake->getPoint(i+1).x) ||         //Угловые части
                            (snake->getPoint(i+1).y < snake->getPoint(i).y && snake->getPoint(i-1).x < snake->getPoint(i).x))
                        snake_px1.load(":/images/red_Angle_lu.png");

                    else if ((snake->getPoint(i+1).y < snake->getPoint(i).y && snake->getPoint(i).x < snake->getPoint(i-1).x) ||
                            (snake->getPoint(i-1).y < snake->getPoint(i).y && snake->getPoint(i+1).x > snake->getPoint(i).x))
                        snake_px1.load(":/images/red_Angle_ur.png");

                    else if ((snake->getPoint(i-1).y > snake->getPoint(i).y && snake->getPoint(i).x < snake->getPoint(i+1).x) ||
                            (snake->getPoint(i+1).y > snake->getPoint(i).y && snake->getPoint(i-1).x > snake->getPoint(i).x))
                        snake_px1.load(":/images/red_Angle_rd.png");

                    else if ((snake->getPoint(i+1).y > snake->getPoint(i).y && snake->getPoint(i).x > snake->getPoint(i-1).x) ||
                            (snake->getPoint(i-1).y > snake->getPoint(i).y && snake->getPoint(i+1).x < snake->getPoint(i).x))
                        snake_px1.load(":/images/red_Angle_dl.png");

                    else if (snake->getPoint(i).x == snake->getPoint(i-1).x)                                                        //Прямые части
                        snake_px1.load(":/images/red_Straight_ver.png");
                    else if (snake->getPoint(i).y == snake->getPoint(i-1).y)
                        snake_px1.load(":/images/red_Straight_hor.png");

                    painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, snake_px1);

                }
                else if (i == 0){
                    QPixmap snake_px;

                    if (x_shift == 0 && y_shift == -20)                               //Текстуры головы
                        snake_px.load(":/images/red_Head_down.png");
                    else if (x_shift == 0 && y_shift == 20)
                        snake_px.load(":/images/red_Head_up.png");
                    else if (x_shift == 20 && y_shift == 0)
                        snake_px.load(":/images/red_Head_left.png");
                    else if (x_shift == -20 && y_shift == 0)
                        snake_px.load(":/images/red_Head_right.png");

                    painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, snake_px);
                }
                else if (i == size - 1){                                                  //Текстуры хвоста
                    QPixmap tail_px;

                    if (snake->getPoint(i-1).y < snake->getPoint(i).y)
                        tail_px.load(":/images/red_Tail_u.png");
                    if (snake->getPoint(i-1).y > snake->getPoint(i).y)
                        tail_px.load(":/images/red_Tail_d.png");
                    if (snake->getPoint(i-1).x > snake->getPoint(i).x)
                        tail_px.load(":/images/red_Tail_r.png");
                    if (snake->getPoint(i-1).x < snake->getPoint(i).x)
                        tail_px.load(":/images/red_Tail_l.png");

                    painter.drawPixmap(snake->getPoint(i).x,  snake->getPoint(i).y, 20, 20, tail_px);

                }
            }
        }
    }


    if(snake->isDied()){
        timer->stop();
        bool ok;
        QString text = QInputDialog::getText(this, tr("Введите ваше имя"),
                                             tr("Ваше имя:"), QLineEdit::Normal,
                                             "Player", &ok);
        if (ok && !text.isEmpty()){
            QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
            QString pathToDB = QDir::currentPath()+QString("/base.sqlite");
             sdb.setDatabaseName(pathToDB);
             sdb.open();
             QSqlQuery a;
             QString queryStr="INSERT INTO Score (Имя, Очки) VALUES ('"+text+"',"+QString::number(score)+");";
             if(!a.exec(queryStr)){
                qDebug()<<a.lastError();
             }
             qDebug()<<sdb.tables();

        }

        close();
        menu->show();
    }
    for(int i=1;i<size;++i){
        if(compare(snake->getPoint(i).x,snake->getPoint(i).y,snake->getPoint(0).x,snake->getPoint(0).y)){
            snake->dieSnake();
            break;
        }
    }
    for(int i=0;i<lets->size;++i){
        if(compare(lets->getPoint(i).x,lets->getPoint(i).y,snake->getPoint(0).x,snake->getPoint(0).y)){
            snake->dieSnake();
            break;
        }
    }
    this->setWindowTitle("У вас "+QString::number(score)+" очков.");
}

void windowGame::paintFood(){

    QPixmap fruit;
    fruit.load(":/images/pills.png");
    if(pear->visibleFood){
        painter.drawPixmap(pear->getPoint(0).x,  pear->getPoint(0).y, 20, 20,fruit);
    }

    fruit.load(":/images/fruit.png");
    if(apple->visibleFood){
        painter.drawPixmap(apple->getPoint(0).x,  apple->getPoint(0).y, 20, 20,fruit);
    }

    fruit.load(":/images/banana.png");
    if(banan->visibleFood){
        painter.drawPixmap(banan->getPoint(0).x,  banan->getPoint(0).y, 20, 20,fruit);
    }


    if(!pear->visibleFood){
        timerFoodPear++;
    }
    if(!apple->visibleFood){
        timerFoodApple++;
    }
    if(!banan->visibleFood){
        timerFoodBanan++;
    }

    if(timerFoodPear==10){
        timerFoodPear=0;
        pear->move();
        while(compareToLets(pear->getPoint(0).x,pear->getPoint(0).y)){
            pear->move();
        }
        pear->visibleFood=true;
    }

    if(timerFoodApple==10){
        timerFoodApple=0;
        apple->move();
        while(compareToLets(apple->getPoint(0).x,apple->getPoint(0).y)){
            apple->move();
        }
        apple->visibleFood=true;
    }

    if(timerFoodBanan==10){
        timerFoodBanan=0;
        banan->move();
        while(compareToLets(banan->getPoint(0).x,banan->getPoint(0).y)){
            banan->move();
        }
        banan->visibleFood=true;
    }
}


void windowGame::paintPortal(){
    QPixmap fruit;
    fruit.load(":/images/black.png");
    painter.drawPixmap(portal->getPoint(0).x,  portal->getPoint(0).y, 20, 20,fruit);
    painter.drawPixmap(portal->getPoint(1).x,  portal->getPoint(1).y, 20, 20,fruit);
}

void windowGame::paintObstacle(){
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    QPixmap pix;
    pix.load(":/images/obstacle.png");
    for(int i=0;i<lets->size;++i){
        painter.drawPixmap(lets->getPoint(i).x,  lets->getPoint(i).y, 20, 20,pix);
    }
}

bool windowGame::compare(int x1, int y1, int x2, int y2){
    if(x1==x2 && y1==y2){
        return true;
    }
    else
        return false;
}

bool windowGame::compareToLets(int x1, int y1){
    for(int i=0;i<lets->size;++i){
        if(x1==lets->getPoint(i).x && y1==lets->getPoint(i).y){
            return true;
        }
    }
    return false;

}



void windowGame::keyPressEvent(QKeyEvent *event){
        switch (event->key()) {
        case 16777235:
            if(y_shift>=0){
               x_shift=0;
               y_shift=20;
            }
            break;
        case 16777237:
            if(y_shift<=0){
                x_shift=0;
                y_shift=-20;
            }
            break;
        case 16777234:
            if(x_shift>=0){
               x_shift=20;
               y_shift=0;
            }
            break;
        case 16777236:
            if(x_shift<=0){
               x_shift=-20;
                y_shift=0;
            }
            break;
        }
}
