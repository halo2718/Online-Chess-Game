#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QDialog>

namespace Ui {
class myClient;
}

class myClient : public QDialog
{
    Q_OBJECT

public:
    explicit myClient(QWidget *parent = nullptr);
    ~myClient();
signals:
    void clientSet(QString);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_buttonBox_accepted();

private:
    Ui::myClient *ui;
};

#endif // MYCLIENT_H
