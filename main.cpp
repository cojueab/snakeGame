#include "windowgame.h"
#include <QApplication>
#include <QTest>
#include "menu.h"
#include <QTime>
#include <QMediaPlayer>
#include <QSqlDatabase>
#include <QMediaPlaylist>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Menu menu;
    menu.show();

    QMediaPlaylist *playlist;

    playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/images/1.wav"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QMediaPlayer *player;
    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(30);
    player->play();
    return a.exec();
}
