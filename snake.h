#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "item.h"

class Snake : public item
{
    Q_OBJECT
public:
    explicit Snake(item *parent = 0);


private:
    bool dieFlag=0;
    int skills=0;


signals:
    void died();

public slots:
    void move(int changeX, int changeY);
    void dieSnake();
    bool isDied();
    void setSkill(int skill);
    void insert(int changeX, int changeY);

    void res();
};

#endif // SNAKE_H
