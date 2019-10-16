//include required header files and libraries
#include "mainwindow.h"
#include <QApplication>
#include "globals.h"

SecCookie SecCookie_Instance;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
