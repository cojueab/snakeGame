#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QColor>
#include <QList>

#include "point.h"

//объект
class item : public QObject
{
    Q_OBJECT
public:
    explicit item(QObject *parent = 0);

signals:

private:
    QList<Point> points;

public slots:
    //назначить
    void setPoints(QList<Point> arr,int n);
    void setPoint(Point t);
    void setPointInsert(Point t);
    void moveEl(int from,int to);
    void changeXY(int x,int y,int i);
    //получить
    QList<Point> getPoints();
    Point getPoint(int i);

    //
    int Counts();
};

#endif // ITEM_H
