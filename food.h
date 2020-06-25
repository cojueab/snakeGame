#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include "item.h"

class food : public item
{
    Q_OBJECT
public:
    explicit food(item *parent = 0);
    bool eatedFlag=false;
    int skill=0;
    bool visibleFood=true;
    void changeColor(QColor color);
signals:
    void eated();
public slots:
    void eat();
    void move();
};

#endif // FOOD_H
