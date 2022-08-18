#include "client.h"
#include "ui_client.h"
#include "QMessageBox"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    init();
}

Client::~Client()
{
    delete ui;
}

void Client::init()
{
    setWindowTitle("Client");
    ui->IP->setPlaceholderText("IP");
    ui->IP->setText("127.0.0.1");
    ui->port->setPlaceholderText("Port");
    ui->port->setText("8888");
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket,&QTcpSocket::connected,[this](){ui->rec_window->setText("connect successfully!");});
    connect(tcpsocket,&QTcpSocket::readyRead,this,&Client::readdata);
}

void Client::readdata()
{
    QString data = tcpsocket->readAll();
    ui->rec_window->setText(data);
}

void Client::on_send_clicked()
{
    if(tcpsocket == nullptr)
        return;
    QString str = ui->send_window->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void Client::on_disconnect_clicked()
{
    if(tcpsocket == nullptr)
        return;
    //断开与服务器的连接
    tcpsocket->disconnectFromHost();
    //关闭通信套接字
    tcpsocket->close();
    this->close();
}

void Client::on_Connect_clicked()
{
    if(ui->IP->toPlainText()==""||ui->port->toPlainText()==""){
        return;
    }
    QString IP = ui->IP->toPlainText();
    int Port = ui->port->toPlainText().toInt();
    tcpsocket->connectToHost(IP,Port);
}
