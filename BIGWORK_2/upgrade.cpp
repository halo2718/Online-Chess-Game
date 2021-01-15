#include "upgrade.h"
#include "ui_upgrade.h"

Upgrade::Upgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Upgrade)
{
    ui->setupUi(this);
}

Upgrade::~Upgrade()
{
    delete ui;
}

void Upgrade::on_pushButton_clicked()
{
    emit upgradeSignal(1);
    this->close();
}

void Upgrade::on_pushButton_2_clicked()
{
    emit upgradeSignal(2);
    this->close();
}

void Upgrade::on_pushButton_3_clicked()
{
    emit upgradeSignal(3);
    this->close();
}

void Upgrade::on_pushButton_4_clicked()
{
    emit upgradeSignal(4);
    this->close();
}
