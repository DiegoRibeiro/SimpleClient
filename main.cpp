#include "mainwindow.h"

#include <QApplication>

int __cdecl main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
