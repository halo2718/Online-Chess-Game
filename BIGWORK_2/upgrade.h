#ifndef UPGRADE_H
#define UPGRADE_H

#include <QWidget>

namespace Ui {
class Upgrade;
}

class Upgrade : public QWidget
{
    Q_OBJECT

public:
    explicit Upgrade(QWidget *parent = nullptr);
    ~Upgrade();
signals:
    void upgradeSignal(int);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Upgrade *ui;
};

#endif // UPGRADE_H
