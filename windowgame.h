#ifndef WINDOWGAME_H
#define WINDOWGAME_H

#include <QWidget>
#include <QPainter>
#include <QSound>
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include "portal.h"
#include "menu.h"

class windowGame : public QWidget
{
    Q_OBJECT

public:
    windowGame(QWidget *parent = 0,QColor windowColor=QColor(Qt::blue),int hard=1,int colorSnake=0,bool intellect=false);
    ~windowGame();

    void start();

    void paintSnake();
    void paintFood();
    void paintObstacle();
    void paintPortal();
    void fCourse();


    bool compare(int x1,int y1,int x2,int y2);
    bool compareToLets(int x1,int y1);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QPainter painter;
    Snake *snake;

    food *pear;
    food *apple;
    food *banan;
    int _colorSnake;
    bool _intellect;
    obstacle *lets;
    bool *course;

    Portal *portal;
    QSound *player;

    QTimer *timer;
    int time;

    int score;
    Menu *menu;


    int x_shift;
    int y_shift;

    int timerFoodPear=0;
    int timerFoodApple=0;
    int timerFoodBanan=0;

    int timeToTime=0;

};

#endif // WINDOWGAME_H
