#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "socket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendBtn_clicked();
    void on_connectBtn_clicked();
    void on_disconnectBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool connected;
    Socket s;
};
#endif // MAINWINDOW_H
