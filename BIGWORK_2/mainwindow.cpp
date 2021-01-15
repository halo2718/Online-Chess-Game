#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new myServer;
    client = new myClient;
    up = new Upgrade;

    ui->lcdNumber->display(60);

    table[0][0]=2;
    table[1][0]=3;
    table[2][0]=4;
    table[3][0]=5;
    table[4][0]=6;
    table[5][0]=4;
    table[6][0]=3;
    table[7][0]=2;

    for(int i=0;i<8;i++)
        table[i][1]=1;
    for(int i=2;i<6;i++)
        for(int j=0;j<8;j++)
            table[j][i]=0;
    for(int i=0;i<8;i++)
        table[i][6]=-1;
    table[0][7]=-2;
    table[1][7]=-3;
    table[2][7]=-4;
    table[3][7]=-5;
    table[4][7]=-6;
    table[5][7]=-4;
    table[6][7]=-3;
    table[7][7]=-2;

    for(int i=0;i<12;i++)
    {
        if(i<6)
            img[i] = new QImage("w"+QString::number(i+1)+".png");
        else
            img[i] = new QImage("b"+QString::number(i-5)+".png");
    }

    timer = new QTimer;
    time = 60;

    connect(timer, SIGNAL(timeout()), this, SLOT(timing()));
    connect(this->server, SIGNAL(serverSet()), this, SLOT(startListening()));
    connect(this->server, SIGNAL(serverDisconnect()), this, SLOT(accepttDisconnection()));
    connect(this->client, SIGNAL(clientSet(QString)), this, SLOT(process(QString)));
    connect(this->up, SIGNAL(upgradeSignal(int)), this, SLOT(upgradeChess(int)));
    connect(this,SIGNAL(sbtcpserver()),this,SLOT(accepttDisconnection()));

    ma['a']=0;
    ma['b']=1;
    ma['c']=2;
    ma['d']=3;
    ma['e']=4;
    ma['f']=5;
    ma['g']=6;
    ma['h']=7;

    am[0]='a';
    am[1]='b';
    am[2]='c';
    am[3]='d';
    am[4]='e';
    am[5]='f';
    am[6]='g';
    am[7]='h';
}

void MainWindow::upgradeChess(int pa)
{
    if(toUpgrade!=std::make_pair(-1,-1))
    {
        int i = toUpgrade.first;
        int j = toUpgrade.second;
        if(pa==1)
            table[i][j]*=5;
        else if(pa==2)
            table[i][j]*=4;
        else if(pa==3)
            table[i][j]*=3;
        else if(pa==4)
            table[i][j]*=2;
        type=6-pa;
    }
    QByteArray array;
    array.append("UPG "+QString::number(toUpgrade.first)+" "+QString::number(toUpgrade.second)+" "+QString::number(type));
    this->sk->write(array.data());
    sk->waitForBytesWritten();
    this->update();
}

void MainWindow::process(QString text)
{
    sk = new QTcpSocket;
    sk->connectToHost(QHostAddress(text),8888);
    if(!sk->waitForConnected(1000))
    {
        QMessageBox::information(this,"info", "No Connection");
        return ;
    }
    this->side=-1;
    turn = 0;
    this->update();
    QMessageBox::information(this,"info", "Connected to server: " + (sk->peerAddress()).toString());
    connect(sk, SIGNAL(readyRead()), this, SLOT(read()));
    connect(sk, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void MainWindow::clientConnected()
{
}

void MainWindow::timing()
{
    time--;
    ui->lcdNumber->display(time);
    if(time==0)
    {
        timer->stop();
        QByteArray array;
        array.clear();
        array.append("TIM out");
        this->sk->write(array.data());
        QMessageBox::information(this,"info", "Time out, you lose!");
        turn = 0;
    }
}

void MainWindow::startListening()
{
    acceptConne=true;
    sv = new QTcpServer;
    sv->listen(QHostAddress::AnyIPv4,8888);
    connect(this->sv,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

void MainWindow::acceptConnection()
{
        turn = 1;
        sk = sv->nextPendingConnection();
        this->side=1;
        time = 60;
        ui->lcdNumber->display(60);
        timer->start(1000);
        connect(sk, SIGNAL(readyRead()), this, SLOT(read()));
        connect(sk, SIGNAL(disconnected()), this, SLOT(disconnected()));
        QMessageBox::information(this,"info", "CONNECTED!");
}

void MainWindow::accepttDisconnection()
{
   if(sv!=nullptr)
    {
       qDebug()<<"1";
        if(sv!=nullptr)
            sv->close();
        qDebug()<<"2";
        return;
    }
   qDebug()<<"3";
//  sk->disconnectFromHost();
    timer->stop();
    time = 60;
    ui->lcdNumber->display(60);
    turn=0;
}

void MainWindow::disconnected()
{
    sk->disconnectFromHost();
    if(turn)  timer->stop();
}

void MainWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    int cx=(width()-ui->groupBox->width())/2+ui->groupBox->width();
    int cy=(height()-ui->menuBar->height())/2;
    int bottom = cy+320;
    int left = cx-320;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if((i+j)%2) p.setBrush(QColor(240,218,181));
            else p.setBrush(QColor(185,131,99));
            p.drawRect(i*80+left, bottom-80-j*80,80,80);
        }
    if(focus.first!=-1&&focus.second!=-1)
    {
        p.setPen(QPen(Qt::blue,4));
        p.setBrush(Qt::NoBrush);
        p.drawRect(focus.first*80+left+5, bottom-80-focus.second*80+5,70,70);
    }

    if(feasiblePos.size()!=0)
    {
        p.setPen(QPen(Qt::green,4));
        p.setBrush(Qt::NoBrush);
        for(int i=0;i<feasiblePos.size();i++)  p.drawRect(feasiblePos[i].first*80+left+5, bottom-80-feasiblePos[i].second*80+5,70,70);
    }

    if(eat.size()!=0)
    {
        p.setPen(QPen(Qt::red,4));
        p.setBrush(Qt::NoBrush);
        for(int i=0;i<eat.size();i++)  p.drawRect(eat[i].first*80+left+5, bottom-80-eat[i].second*80+5,70,70);
    }

    if(isChange.size()!=0)
    {
        p.setPen(QPen(Qt::yellow,4));
        p.setBrush(Qt::NoBrush);
        for(int i=0;i<isChange.size();i++)  p.drawRect(isChange[i].first*80+left+5, bottom-80-isChange[i].second*80+5,70,70);
    }

    QRect obj(0,0,291,291);
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            QRect trg(i*80+left,bottom-80-80*j,80,80);
            switch(table[i][j])
            {
                case 1: p.drawImage(trg,*img[0],obj); break;
                case 2: p.drawImage(trg,*img[1],obj); break;
                case 3: p.drawImage(trg,*img[2],obj); break;
                case 4: p.drawImage(trg,*img[3],obj); break;
                case 5: p.drawImage(trg,*img[4],obj); break;
                case 6: p.drawImage(trg,*img[5],obj); break;
                case -1: p.drawImage(trg,*img[6],obj); break;
                case -2: p.drawImage(trg,*img[7],obj); break;
                case -3: p.drawImage(trg,*img[8],obj); break;
                case -4: p.drawImage(trg,*img[9],obj); break;
                case -5: p.drawImage(trg,*img[10],obj); break;
                case -6: p.drawImage(trg,*img[11],obj); break;
                default: break;
            }
        }
}

void MainWindow::read()
{
    QString info = "";
    bool hasUp=false;
    info.append(sk->readAll());
    qDebug()<<info;
    QStringList operation = info.split(' ');
    if(operation[0]=="MOV")
    {
        std::swap(table[operation[1].toInt()][operation[2].toInt()],table[operation[3].toInt()][operation[4].toInt()]);
        if(operation.size()>5)
            hasUp=true;
        turn = 1;
        timer->start(1000);
    }
    else if(operation[0]=="EAT")
    {
        table[operation[3].toInt()][operation[4].toInt()]=0;
        std::swap(table[operation[1].toInt()][operation[2].toInt()],table[operation[3].toInt()][operation[4].toInt()]);
        if(operation.size()>5)
            hasUp=true;
        turn = 1;
        timer->start(1000);
    }
    else if(operation[0]=="SUR")
    {
        QMessageBox::information(this,"info", "Your opponent surrenders, you win!");
    }
    else if(operation[0]=="TIM")
    {
        QMessageBox::information(this,"info", "Your opponent ran out of time, you win!");
    }
    else if(operation[0]=="CHE")
    {
        QMessageBox::information(this,"info", "Checkmate, you lose!");
    }
    else if(operation[0]=="UPG")
    {
        table[operation[1].toInt()][operation[2].toInt()]*=operation[3].toInt();
        turn = 1;
        timer->start(1000);
    }
    else if(operation[0]=="CHA")
    {
        int a = operation[1].toInt();
        int b = operation[2].toInt();
        int c = operation[3].toInt();
        int d = operation[4].toInt();
        if(c==0)
        {
            table[2][b]=table[4][b];
            table[3][b]=table[0][b];
            table[4][b]=0;
            table[0][b]=0;
        }
        else
        {
            table[6][b]=table[4][b];
            table[5][b]=table[7][b];
            table[4][b]=0;
            table[7][b]=0;
        }
        turn = 1;
        timer->start(1000);
    }
    else if(operation[0]=="TIE")
    {
        QMessageBox::information(this,"info", "TIE");
        this->timer->stop();
        turn=0;
    }
    else if(operation[0]=="RES")
    {
        table[0][0]=2;
        table[1][0]=3;
        table[2][0]=4;
        table[3][0]=5;
        table[4][0]=6;
        table[5][0]=4;
        table[6][0]=3;
        table[7][0]=2;

        for(int i=0;i<8;i++)
            table[i][1]=1;
        for(int i=2;i<6;i++)
            for(int j=0;j<8;j++)
                table[j][i]=0;
        for(int i=0;i<8;i++)
            table[i][6]=-1;
        table[0][7]=-2;
        table[1][7]=-3;
        table[2][7]=-4;
        table[3][7]=-5;
        table[4][7]=-6;
        table[5][7]=-4;
        table[6][7]=-3;
        table[7][7]=-2;

        this->time=60;
        this->timer->stop();
        turn = 0;
        side= -1;
        eat.clear();
        feasiblePos.clear();
        isChange.clear();
        focus={-1,-1};
        toUpgrade={-1,-1};
    }
    if(isTie()&&!hasUp)
    {
        QByteArray array;
        array.append("TIE");
        this->sk->write(array.data());
        sk->waitForBytesWritten();
        QMessageBox::information(this,"info", "TIE");
        this->timer->stop();
    }
    this->update();
}

void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    if(turn==0) return;

    int cx=(width()-ui->groupBox->width())/2+ui->groupBox->width();
    int cy=(height()-ui->menuBar->height())/2;
    int bottom = cy+320;
    int left = cx-320;
    int i=(ev->x()-left)/80;
    int j=(bottom-ev->y())/80;
    if(ev->button()==Qt::LeftButton)
    {
        bool flag=true;
        if(focus.first!=-1&&focus.second!=-1)
        {
            for(int m=0;m<feasiblePos.size();m++)
                if(feasiblePos[m].first==i&&feasiblePos[m].second==j)
                {
                    std::swap(table[i][j],table[focus.first][focus.second]);
                    flag=false;
                    turn=0;
                    if((table[i][j]==1&&j==7)||(table[i][j]==-1&&j==0))
                    {
                        toUpgrade={i,j};
                        this->up->show();
                        QByteArray array;
                        array.append("MOV "+QString::number(focus.first)+" "+QString::number(focus.second)+" "+QString::number(i)+" "+QString::number(j)+" UPG");
                        this->sk->write(array.data());
                        timer->stop();
                        time=60;
                    }
                    else
                    {
                        QByteArray array;
                        array.append("MOV "+QString::number(focus.first)+" "+QString::number(focus.second)+" "+QString::number(i)+" "+QString::number(j));
                        this->sk->write(array.data());
                        sk->waitForBytesWritten();
                        timer->stop();
                        time=60;
                    }
                }
            for(int m=0;m<isChange.size();m++)
            {
                if(isChange[m].first==i&&isChange[m].second==j)
                {
                    if(i==6)
                    {
                        table[6][j]=table[4][j];
                        table[5][j]=table[7][j];
                        table[4][j]=0;
                        table[7][j]=0;
                        QByteArray array;
                        array.append("CHA "+QString::number(4)+" "+QString::number(j)+" "+QString::number(7)+" "+QString::number(j));
                        this->sk->write(array.data());
                    }
                    else if(i==2)
                    {
                        table[2][j]=table[4][j];
                        table[3][j]=table[0][j];
                        table[4][j]=0;
                        table[0][j]=0;
                        QByteArray array;
                        array.append("CHA "+QString::number(4)+" "+QString::number(j)+" "+QString::number(0)+" "+QString::number(j));
                        this->sk->write(array.data());
                    }
                    flag=false;
                    turn=0;
                    timer->stop();
                    time=60;
                }
            }
            for(int m=0;m<eat.size();m++)
                if(eat[m].first==i&&eat[m].second==j)
                {
                    table[i][j]=0;
                    std::swap(table[i][j],table[focus.first][focus.second]);
                    flag=false;
                    turn=0;
                    if(!judgeWin())
                    {
                        if((table[i][j]==1&&j==7)||(table[i][j]==-1&&j==0))
                        {
                            toUpgrade={i,j};
                            this->up->show();
                            QByteArray array;
                            array.append("EAT "+QString::number(focus.first)+" "+QString::number(focus.second)+" "+QString::number(i)+" "+QString::number(j)+" UPG");
                            this->sk->write(array.data());
                            sk->waitForBytesWritten();
                        }
                        else
                        {
                            QByteArray array;
                            array.append("EAT "+QString::number(focus.first)+" "+QString::number(focus.second)+" "+QString::number(i)+" "+QString::number(j));
                            this->sk->write(array.data());
                            sk->waitForBytesWritten();
                            this->timer->stop();
                            this->time=60;
                        }
                    }
                    else
                    {
                        QByteArray array;
                        array.append(" "+QString::number(focus.first)+" "+QString::number(focus.second)+" "+QString::number(i)+" "+QString::number(j));
                        this->sk->write(array.data());
                        QMessageBox::information(this,"info", "You win!");
                    }
                    timer->stop();
                    time=60;
                }
        }
        focus.first=-1;
        focus.second=-1;
        feasiblePos.clear();
        eat.clear();
        isChange.clear();
        if(i<8&&i>=0&&j<8&&j>=0&&table[i][j]!=0&&flag&&turn*table[i][j]!=0&&side*table[i][j]>0)
        {
            focus={i,j};
            showNext(table[i][j],i,j);
        }
    }
    this->update();
}

void MainWindow::showNext(int type, int x, int y)
{
    if(type==1)
    {
        if(y==1)
        {
            for(int i=0;i<2;i++)
            {
                if(table[x][y+i+1])  break;
                else feasiblePos.push_back({x,y+i+1});
            }
        }
        else
        {
            if(table[x][y+1]){}
            else feasiblePos.push_back({x,y+1});
        }
        if(x+1<8&&y+1<8&&table[x+1][y+1]<0)  eat.push_back({x+1,y+1});
        if(x-1>=0&&y+1<8&&table[x-1][y+1]<0)  eat.push_back({x-1,y+1});
    }
    if(type==-1)
    {
        if(y==6)
        {
            for(int i=0;i<2;i++)
            {
                if(table[x][y-i-1])  break;
                else feasiblePos.push_back({x,y-i-1});
            }
        }
        else
        {
            if(table[x][y-1]){}
            else feasiblePos.push_back({x,y-1});
        }
        if(x+1<8&&y-1>=0&&table[x+1][y-1]>0)  eat.push_back({x+1,y-1});
        if(x-1>=0&&y-1>=0&&table[x-1][y-1]>0)  eat.push_back({x-1,y-1});
    }
    if(type==2||type==-2)
    {
        int tx=x+1,ty=y;
        while(tx<8) {if(table[tx][ty]==0)  feasiblePos.push_back({tx++,ty});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y;
        while(tx>=0) {if(table[tx][ty]==0)  feasiblePos.push_back({tx--,ty});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x;ty=y+1;
        while(ty<8) {if(table[tx][ty]==0)  feasiblePos.push_back({tx,ty++});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x;ty=y-1;
        while(ty>=0) {if(table[tx][ty]==0)  feasiblePos.push_back({tx,ty--});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}

    }
    if(type==3||type==-3)
    {
        if(x-1>=0&&y+2<8&&table[x-1][y+2]*table[x][y]<=0) (table[x-1][y+2]*table[x][y]==0)? feasiblePos.push_back({x-1,y+2}):eat.push_back({x-1,y+2});
        if(x-1>=0&&y-2>=0&&table[x-1][y-2]*table[x][y]<=0) (table[x-1][y-2]*table[x][y]==0)? feasiblePos.push_back({x-1,y-2}):eat.push_back({x-1,y-2});
        if(x-2>=0&&y+1<8&&table[x-2][y+1]*table[x][y]<=0) (table[x-2][y+1]*table[x][y]==0)? feasiblePos.push_back({x-2,y+1}):eat.push_back({x-2,y+1});
        if(x-2>=0&&y-1>=0&&table[x-2][y-1]*table[x][y]<=0) (table[x-2][y-1]*table[x][y]==0)? feasiblePos.push_back({x-2,y-1}):eat.push_back({x-2,y-1});
        if(x+1<8&&y+2<8&&table[x+1][y+2]*table[x][y]<=0)  (table[x+1][y+2]*table[x][y]==0)? feasiblePos.push_back({x+1,y+2}):eat.push_back({x+1,y+2});
        if(x+1<8&&y-2>=0&&table[x+1][y-2]*table[x][y]<=0)  (table[x+1][y-2]*table[x][y]==0)? feasiblePos.push_back({x+1,y-2}):eat.push_back({x+1,y-2});
        if(x+2<8&&y+1<8&&table[x+2][y+1]*table[x][y]<=0)  (table[x+2][y+1]*table[x][y]==0)? feasiblePos.push_back({x+2,y+1}):eat.push_back({x+2,y+1});
        if(x+2<8&&y-1>=0&&table[x+2][y-1]*table[x][y]<=0)  (table[x+2][y-1]*table[x][y]==0)? feasiblePos.push_back({x+2,y-1}):eat.push_back({x+2,y-1});
    }
    if(type==4||type==-4)
    {
        int tx=x+1,ty=y+1;
        while(tx<8&&ty<8) {if(table[tx][ty]==0)  {feasiblePos.push_back({tx,ty});tx++;ty++;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x+1;ty=y-1;
        while(tx<8&&ty>=0) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx++;ty--;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y+1;
        while(tx>=0&&ty<8) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx--;ty++;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y-1;
        while(tx>=0&&ty>=0) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx--;ty--;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
    }
    if(type==5||type==-5)
    {
        int tx=x+1,ty=y+1;
        while(tx<8&&ty<8) {if(table[tx][ty]==0)  {feasiblePos.push_back({tx,ty});tx++;ty++;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x+1;ty=y-1;
        while(tx<8&&ty>=0) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx++;ty--;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y+1;
        while(tx>=0&&ty<8) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx--;ty++;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y-1;
        while(tx>=0&&ty>=0) {if(table[tx][ty]==0)   {feasiblePos.push_back({tx,ty});tx--;ty--;}else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x+1;ty=y;
        while(tx<8) {if(table[tx][ty]==0)  feasiblePos.push_back({tx++,ty});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x-1;ty=y;
        while(tx>=0) {if(table[tx][ty]==0)  feasiblePos.push_back({tx--,ty});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x;ty=y+1;
        while(ty<8) {if(table[tx][ty]==0)  feasiblePos.push_back({tx,ty++});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
        tx=x;ty=y-1;
        while(ty>=0) {if(table[tx][ty]==0)  feasiblePos.push_back({tx,ty--});else if(table[tx][ty]*table[x][y]<0) {eat.push_back({tx,ty});break;} else break;}
    }
    if(type==6||type==-6)
    {
        for(int i=x-1;i<x+2;i++)
            for(int j=y-1;j<y+2;j++)
                if(i<8&&i>=0&&j<8&&j>=0&&table[i][j]==0)
                    feasiblePos.push_back({i,j});
                else if(i<8&&i>=0&&j<8&&j>=0&&table[i][j]*table[x][y]<0)
                    eat.push_back({i,j});
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_Host_triggered()
{
    this->server->show();
}

void MainWindow::on_actionConnect_to_Host_triggered()
{
    this->client->show();
}

void MainWindow::on_pushButton_clicked()
{
    if(sk==NULL)
        return;
    QByteArray array;
    array.append("SUR");
    this->sk->write(array);
    turn=0;
    timer->stop();
    QMessageBox::information(this,"info", "You Lose!");
}

bool MainWindow::judgeWin()
{
    bool flag = true;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(table[i][j]==-side*6)
                flag = false;
    if(flag)
    {
        QByteArray array;
        array.append("CHE");
        this->sk->write(array);
    }

    return flag;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"./","Text files (*.txt)");
    if(fileName == "")  return;
    QFile filename(fileName);
    if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Error",tr("Failed!"));
        return;
    }
    else
    {
        QTextStream textStream(&filename);
        int cnt = 0;
        std::vector<std::pair<int,int>> tmp;
        QString str = "white";
        textStream<<str<<"\n";
        str="pawn ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==1)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        tmp.clear();
        cnt=0;
        textStream<<str;
        str="rook ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==2)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="knight ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==3)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="bishop ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==4)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="queen ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==5)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="king ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==6)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="black\n";
        textStream<<str;
        str="pawn ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-1)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        tmp.clear();
        cnt=0;
        textStream<<str;
        str="rook ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-2)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="knight ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-3)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="bishop ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-4)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="queen ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-5)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
        str="king ";
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(table[i][j]==-6)
                {
                    cnt++;
                    tmp.push_back({i,j});
                }
        if(cnt!=0)
        {
            str+=QString::number(cnt)+" ";
            for(int i=0;i<tmp.size();i++)
            {
                if(i!=tmp.size()-1)
                    str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+" ";
                else  str+=am[tmp[i].first]+QString::number(tmp[i].second+1)+"\n";
            }
        }
        textStream<<str;
        tmp.clear();
        cnt=0;
    }
    filename.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open image file"),"./", tr("Text files (*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Error",tr("Failed!"));
        return;
   }
   for(int i=0;i<8;i++)
       for(int j=0;j<8;j++)
           table[i][j]=0;
   QTextStream txtInput(&file);
   txtInput.setCodec("gb18030");
   QString str;
   int color=0;
   while(!txtInput.atEnd())
   {
       str =txtInput.readLine();
       if(str=="white")  color=1;
       else if(str=="black")  color=-1;

       QStringList condi = str.split(" ");
       if(condi[0]=="pawn")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=1*color;
           }
       }
       if(condi[0]=="rook")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=2*color;
           }
       }
       if(condi[0]=="knight")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=3*color;
           }
       }
       if(condi[0]=="bishop")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=4*color;
           }
       }
       if(condi[0]=="queen")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=5*color;
           }
       }
       if(condi[0]=="king")
       {
           int size = condi[1].toInt();
           for(int i=2;i<2+size;i++)
           {
               QStringList pro = condi[i].split("");
               char s = condi[i][0].toLatin1();
               table[ma[s]][pro[2].toInt()-1]=6*color;
           }
       }
   }
   file.close();
   this->update();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(side>0)
    {
        if(table[4][0]==6&&table[7][0]==2&&table[5][0]==0&&table[6][0]==0)
        {
            if(isCheckmate(5,0)&&isCheckmate(6,0)&&isCheckmate(4,0))
            {
                isChange.push_back({6,0});
                focus={99,99};
            }
        }
        if(table[4][0]==6&&table[0][0]==2&&table[3][0]==0&&table[2][0]==0&&table[1][0]==0)
        {
            if(isCheckmate(3,0)&&isCheckmate(2,0)&&isCheckmate(4,0))
            {
                isChange.push_back({2,0});
                focus={99,99};
            }
        }
    }
    else
    {
        if(table[4][7]==-6&&table[7][7]==-2&&table[5][7]==0&&table[6][7]==0)
        {
            if(isCheckmate(5,7)&&isCheckmate(6,7)&&isCheckmate(4,7))
            {
                isChange.push_back({6,7});
                focus={99,99};
            }
        }
        if(table[4][7]==-6&&table[0][7]==-2&&table[3][7]==0&&table[2][7]==0&&table[1][7]==0)
        {
            if(isCheckmate(3,7)&&isCheckmate(2,7)&&isCheckmate(4,7))
            {
                isChange.push_back({2,7});
                focus={99,99};
            }
        }
    }
    this->update();
}

bool MainWindow::isCheckmate(int x, int y)
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(side*table[i][j]<0&&abs(table[i][j])!=1)
                showNext(table[i][j],i,j);
            if(abs(table[i][j])==1)
            {
                if(table[i][j]==1)
                {
                    eat.push_back({i+1,j+1});
                    eat.push_back({i-1,j+1});
                }
                if(table[i][j]==-1)
                {
                    eat.push_back({i+1,j-1});
                    eat.push_back({i-1,j-1});
                }
            }
        }
    bool flag = true;
    for(int i=0;i<feasiblePos.size();i++)
    {
        int sx = feasiblePos[i].first;
        int sy = feasiblePos[i].second;
        if(sx==x&&sy==y)  flag=false;
    }
    for(int i=0;i<eat.size();i++)
    {
        int sx = eat[i].first;
        int sy = eat[i].second;
        if(sx==x&&sy==y)  flag=false;
    }

    feasiblePos.clear();
    eat.clear();

    return flag;
}

bool MainWindow::isTie()
{
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            store[i][j]=table[i][j];
    int x=-1;
    int y=-1;
    bool flag=true;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(table[i][j]==side*6)
            {
                x=i;
                y=j;
            }
    if(!isCheckmate(x,y))
        flag=false;
    bool nolive = true;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            int x0 = x+i-1;
            int y0 = y+j-1;
            if(x0<8&&y0<8&&x0>=0&&y0>=0)
                if(!(x==x0&&y==y0))
                {
                    if(table[x0][y0]*side<=0)
                    {
                        table[x0][y0]=0;
                        std::swap(table[x0][y0],table[x][y]);
                        if(isCheckmate(x0,y0))
                        {
                            qDebug()<<"INVALID"<<x0<<y0;
                            nolive = false;
                        }
                    }
                    for(int k=0;k<8;k++)
                        for(int l=0;l<8;l++)
                            table[k][l]=store[k][l];
                }
        }
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(table[i][j]*side>0&&abs(table[i][j])!=6)
            {
                showNext(table[i][j],i,j);
                std::vector<std::pair<int,int>> tmp1 = feasiblePos;
                std::vector<std::pair<int,int>> tmp2 = eat;
                feasiblePos.clear();
                eat.clear();
                for(int k=0;k<tmp1.size();k++)
                {
                    std::swap(table[i][j],table[tmp1[k].first][tmp1[k].second]);
                    if(isCheckmate(x,y))
                    {
                        nolive = false;
                    }
                    for(int p=0;p<8;p++)
                        for(int q=0;q<8;q++)
                            table[p][q]=store[p][q];
                }
                for(int k=0;k<tmp2.size();k++)
                {
                    table[tmp2[k].first][tmp2[k].second]=0;
                    std::swap(table[i][j],table[tmp2[k].first][tmp2[k].second]);
                    if(isCheckmate(x,y))
                    {
                        nolive = false;
                    }
                    for(int p=0;p<8;p++)
                        for(int q=0;q<8;q++)
                            table[p][q]=store[p][q];
                }
            }
        }
    if(flag&&nolive)  return true;
    else return false;
}

void MainWindow::on_pushButton_5_clicked()
{
    table[0][0]=2;
    table[1][0]=3;
    table[2][0]=4;
    table[3][0]=5;
    table[4][0]=6;
    table[5][0]=4;
    table[6][0]=3;
    table[7][0]=2;

    for(int i=0;i<8;i++)
        table[i][1]=1;
    for(int i=2;i<6;i++)
        for(int j=0;j<8;j++)
            table[j][i]=0;
    for(int i=0;i<8;i++)
        table[i][6]=-1;
    table[0][7]=-2;
    table[1][7]=-3;
    table[2][7]=-4;
    table[3][7]=-5;
    table[4][7]=-6;
    table[5][7]=-4;
    table[6][7]=-3;
    table[7][7]=-2;

    this->time=60;
    timer->start(1000);
    turn = 1;
    side=1;
    eat.clear();
    feasiblePos.clear();
    isChange.clear();
    focus={-1,-1};
    toUpgrade={-1,-1};

    QByteArray array;
    array.append("RES");
    this->sk->write(array.data());

    this->update();
}

void MainWindow::on_pushButton_6_clicked()
{
    emit sbtcpserver();
}
