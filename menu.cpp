#include "menu.h"
#include "ui_menu.h"
#include "windowgame.h"
#include <QColorDialog>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QDir>
Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    myColor=Qt::blue;
    view=new QTableView;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{

    windowGame *win;
    int hard;
    int color;
    if(ui->radioButton->isChecked()){
        hard=0;
    }
    if(ui->radioButton_2->isChecked()){
        hard=1;
    }
    if(ui->radioButton_3->isChecked()){
        hard=2;
    }
    if(ui->radioButton_4->isChecked()){
        color=1;
    }
    if(ui->radioButton_5->isChecked()){
        color=0;
    }
    win=new windowGame(0,myColor,hard,color,ui->checkBox->isChecked());

    win->show();
    close();
}

void Menu::on_pushButton_4_clicked()
{
    myColor=QColorDialog::getColor();
    qDebug()<<myColor.name();
}

void Menu::on_pushButton_2_clicked()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    QString pathToDB = QDir::currentPath()+QString("/base.sqlite");
     sdb.setDatabaseName(pathToDB);
     sdb.open();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM Score");
    model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(1, Qt::Horizontal, tr("Очки"));
    view->setModel(model);
    view->show();
}
