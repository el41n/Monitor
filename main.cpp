#include "mainwindow.h"
#include <QApplication>

#include "cpu.h"
#include <QDebug>
#include <iostream>
#include <windows.h>
#include "architectureproxy.h"
#include "ram.h"

#include "disk.h"


using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<double> >("tuple");

    QApplication a(argc, argv);
    try
    {
        MainWindow w;
        w.show();
          return a.exec();
    }
    catch(std::runtime_error err)
    {
        err.what();
    }


}
