#include "obstacle.h"

obstacle::obstacle(item *parent) : item(parent)
{
    size=qrand()%10;
    int xx=(qrand()%(640/40-2)+1) * 40+20;
    int yy=(qrand()%(480/40-2)+1) * 40+20;
    for(int i=0;i<size;++i){
        int diff_1=my_geration();
        int diff_2=my_geration();
        Point t;
        t.x=xx+diff_1*i;
        t.y=yy+diff_2*i;
        setPoint(t);
    }
}

int obstacle::my_geration(){
    int rand[3];
    rand[0]=-20;
    rand[1]=0;
    rand[2]=20;
    return rand[qrand()%3];
}
