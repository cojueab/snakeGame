#ifndef PORTAL_H
#define PORTAL_H

#include "item.h"

class Portal : public item
{
    Q_OBJECT
public:
    explicit Portal(item *parent = 0);

signals:

public slots:
    void move();
};

#endif // PORTAL_H
