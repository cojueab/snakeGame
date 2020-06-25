#include "item.h"

item::item(QObject *parent) : QObject(parent)
{

}

void item::setPoint(Point t){
    points.append(t);
}

void item::setPointInsert(Point t){
    points.insert(0,t);
}

void item::setPoints(QList<Point> arr, int n){

}

void item::changeXY(int x, int y, int i){
    points[i].x=x;
    points[i].y=y;
}

QList<Point> item::getPoints(){
    QList<Point> items;
    return items;
}

void item::moveEl(int from,int to){
    points.move(from,to);
}

Point item::getPoint(int i){
    return points.at(i);
}

int item::Counts(){
    return points.count();
}
