#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "item.h"

class obstacle : public item
{
    Q_OBJECT
public:
    explicit obstacle(item *parent = 0);
    int size;
signals:

public slots:
    int my_geration();
};

#endif // OBSTACLE_H
