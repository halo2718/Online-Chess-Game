#ifndef MYSERVER_H
#define MYSERVER_H

#include <QDialog>

namespace Ui {
class myServer;
}

class myServer : public QDialog
{
    Q_OBJECT

public:
    explicit myServer(QWidget *parent = nullptr);
    ~myServer();
signals:
    void serverSet();
    void serverDisconnect();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
private:
    Ui::myServer *ui;
};

#endif // MYSERVER_H
