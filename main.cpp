#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;       // create obj
    w.show();           // show obj
    return a.exec();    //loop in which events are handled
}
