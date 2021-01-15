#include "myclient.h"
#include "ui_myclient.h"
#include <QHostAddress>
#include <QMessageBox>

myClient::myClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myClient)
{
    ui->setupUi(this);
}

myClient::~myClient()
{
    delete ui;
}

void myClient::on_pushButton_clicked()
{
    QString content = ui->lineEdit->text();
    content += "0";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_2_clicked()
{
    QString content = ui->lineEdit->text();
    content += "1";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_3_clicked()
{
    QString content = ui->lineEdit->text();
    content += "2";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_4_clicked()
{
    QString content = ui->lineEdit->text();
    content += "3";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_5_clicked()
{
    QString content = ui->lineEdit->text();
    content += "4";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_6_clicked()
{
    QString content = ui->lineEdit->text();
    content += "5";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_7_clicked()
{
    QString content = ui->lineEdit->text();
    content += "6";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_8_clicked()
{
    QString content = ui->lineEdit->text();
    content += "7";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_9_clicked()
{
    QString content = ui->lineEdit->text();
    content += "8";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_10_clicked()
{
    QString content = ui->lineEdit->text();
    content += "9";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_11_clicked()
{
    QString content = ui->lineEdit->text();
    content += ".";
    ui->lineEdit->setText(content);
}

void myClient::on_pushButton_12_clicked()
{
    ui->lineEdit->clear();
}

void myClient::on_buttonBox_accepted()
{
    QString text = ui->lineEdit->text();
    QHostAddress addr(text);
    if(addr.toString()!=text)
    {
        QMessageBox::warning(NULL,"error","error");
    }
    else
    {
        emit clientSet(text);
        this->close();
    }
}
