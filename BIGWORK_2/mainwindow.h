#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "myclient.h"
#include "myserver.h"
#include "upgrade.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    int table[8][8];
    int store[8][8];
    QImage* img[12];
    std::pair<int,int> focus={-1,-1};
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void read();
    void startListening();
    void acceptConnection();
    void accepttDisconnection();
    void clientConnected();
    void disconnected();
    void timing();
    void process(QString);
    void on_actionCreate_Host_triggered();
    void on_actionConnect_to_Host_triggered();
    void upgradeChess(int);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
signals:
    void sbtcpserver();
private:
    int time;
    int turn=0;
    int type=0;
    int side=0;
    bool acceptConne=false;
    std::pair<int,int>toUpgrade={-1,-1};
    QTimer* timer;
    myClient* client;
    myServer* server;
    Upgrade* up;
    QTcpSocket* sk;
    QTcpServer* sv;
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void showNext(int type,int x,int y);
    void pawnUpgrade(int,int);
    bool judgeWin();
    bool isTie();
    bool isCheckmate(int x,int y);
    std::map<char,int>ma;
    std::map<int,char>am;
    std::vector<std::pair<int,int>> eat;
    std::vector<std::pair<int,int>> isChange;
    std::vector<std::pair<int,int>> feasiblePos;
};

#endif // MAINWINDOW_H
