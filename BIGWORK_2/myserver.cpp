#include "myserver.h"
#include "ui_myserver.h"
#include <QHostInfo>
#include <QHostAddress>

myServer::myServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myServer)
{
    ui->setupUi(this);
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug()<<"IP Address："<< info.addresses();
    foreach(QHostAddress address,info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            ui->lineEdit->setText(address.toString());
    }
}

myServer::~myServer()
{
    delete ui;
}

void myServer::on_buttonBox_accepted()
{
    emit serverSet();
    this->close();
}

void myServer::on_buttonBox_rejected()
{
    qDebug()<<"Signal";
    emit serverDisconnect();
    this->close();
    qDebug()<<"Signal";
}
