#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connected = false;
    //this->ui->disconnectBtn->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectBtn_clicked()
{
    this->s = Socket("localhost", "27015");
    this->s.connectTo();
    //this->connected = !this->connected;
    //this->ui->connectBtn->setDisabled(this->connected);
    //this->ui->disconnectBtn->setDisabled(!this->connected);
}

void MainWindow::on_disconnectBtn_clicked()
{
    this->s.disconnect();

    //this->connected = !this->connected;
    //this->ui->connectBtn->setDisabled(this->connected);
    //this->ui->disconnectBtn->setDisabled(!this->connected);
}


void MainWindow::on_sendBtn_clicked()
{
    this->s.sendMessage(this->ui->messageInput->toPlainText());
    this->ui->messageInput->clear();
    /*if(this->connected) {
        QString msg = this->ui->messageInput->toPlainText();
        this->ui->messageOutput->append(msg);

    }
    else {
        QMessageBox alert;
        alert.setText("Please connect to the server!");
        alert.exec();
    }*/
}


