#include "portal.h"
#include <QTime>

Portal::Portal(item *parent) : item(parent)
{
    Point t;
    t.x=300;
    t.y=300;
    setPoint(t);
    setPoint(t);
    move();
}
void Portal::move(){
    changeXY((qrand()%(640/40-2)+1) * 40+20,(qrand()%(480/40-2)+1) * 40+20,0);
    changeXY((qrand()%(640/40-2)+1) * 40+20,(qrand()%(480/40-2)+1) * 40+20,1);
}

