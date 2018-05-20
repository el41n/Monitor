#include "mainwindow.h"
#include <QApplication>

#include "cpu.h"
#include "gpu.h"
#include <QDebug>
#include <iostream>
#include <windows.h>
#include "systemInfo.h"
#include "architectureproxy.h"
#include "ram.h"


using namespace std;

int main(int argc, char *argv[])
{


//    ArchitectureProxy ax = ArchitectureProxy();

//    qDebug() << ax.vendorMessage();
//    ax.mapArchitecture();
//    qDebug() << ax.getMicroArchitecture();
//    qDebug() << ax.getCore();
//    //qDebug() << ax.getMicroArchitecture();
//    systemInformation s = systemInformation();
//    s.getProcInfo();
    QApplication a(argc, argv);
    //SYSTEM_INFO sysInfo;
    //GetSystemInfo(&sysInfo);
    MainWindow w;
    w.show();

    return a.exec();
}
