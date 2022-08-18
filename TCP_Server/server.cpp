#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
    init();
}

Server::~Server()
{
    delete ui;
}

void Server::init()
{
    tcpserver = new QTcpServer(this);
    //监听所有到来的ip，端口为8888
    tcpserver->listen(QHostAddress::Any,8888);
    connect(tcpserver,&QTcpServer::newConnection,this,&Server::newconnect);
}

void Server::newconnect()
{
    tcpsocket = tcpserver->nextPendingConnection();
    QString ip = tcpsocket->peerAddress().toString();
    quint16 port = tcpsocket->peerPort();
    QString temp = QString("Client %1:%2 connect successfully!").arg(ip).arg(port);
    ui->Rec_window->setText(temp);
    connect(tcpsocket,&QTcpSocket::readyRead,this,&Server::readdata);
}

void Server::readdata()
{
    QString data = tcpsocket->readAll();
    ui->Rec_window->setText(data);
}

void Server::on_Send_clicked()
{
    if(tcpsocket == nullptr)
        return;
    QString str = ui->Send_window->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void Server::on_Exit_clicked()
{
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    tcpsocket = nullptr;
    this->close();
}
