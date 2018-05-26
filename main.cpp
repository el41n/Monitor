#include "mainwindow.h"
#include <QApplication>"
#include "disk.h"

using namespace std;

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<double> >("tuple");
    Disk d;
    int b = d.getDiskAmount();

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
