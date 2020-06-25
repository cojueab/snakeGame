#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QColor>
#include <QSound>
#include <QTableView>
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
signals:
    void start();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Menu *ui;
    QColor myColor;
    QTableView *view;
};

#endif // MENU_H
