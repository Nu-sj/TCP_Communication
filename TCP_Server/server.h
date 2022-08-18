#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void init();
    void newconnect();
    void readdata();
    void on_Send_clicked();
    void on_Exit_clicked();

private:
    Ui::Server *ui;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
};
#endif // SERVER_H
