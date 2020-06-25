#include "food.h"
#include <QTime>
#include <QDebug>

food::food(item *parent) : item(parent)
{
    Point t;
    t.x=300;
    t.y=300;
    setPoint(t);
    move();
    qDebug()<<getPoint(0).x;
    qDebug()<<getPoint(0).y;
}
void food::eat(){

}
void food::move(){
    changeXY((qrand()%(640/40-2)+1) * 40+20,(qrand()%(480/40-2)+1) * 40+20,0);
}
