#include "snake.h"
#include <QDebug>

Snake::Snake(item *parent) : item(parent)
{
    int diff=20;
    for(int i=0;i<2;++i){
        Point t;
        t.x=200+diff*i;
        t.y=200;
        setPoint(t);
    }

}

void Snake::move(int changeX, int changeY){
    int xx;
    int yy;
    if(getPoint(0).x-changeX/2>=640){
        xx=0;
    }
    if(getPoint(0).x-changeX*2<=0){
        xx=640;
    }

    if(getPoint(0).y-changeX/2>=480){
        yy=0;
    }
    if(getPoint(0).y-changeX*2<=0){
        yy=480;
    }

    if(getPoint(0).x-changeX>=0 && getPoint(0).x-changeX<=640){
        xx=getPoint(0).x-changeX;
    }
    if(getPoint(0).y-changeY>=0 && getPoint(0).y-changeY<=480){
        yy=getPoint(0).y-changeY;
    }

    changeXY(xx,yy,Counts()-1);
    moveEl(Counts()-1,0);
}

void Snake::insert(int changeX, int changeY){
    Point t;
    t.x=getPoint(0).x-changeX;
    t.y=getPoint(0).y-changeY;
    setPoint(t);
}

void Snake::setSkill(int skill){
    skills=skill;
}

void Snake::dieSnake(){
    dieFlag=true;
}
void Snake::res(){
    dieFlag=false;
}

bool Snake::isDied(){
    return dieFlag;

}
