#include "hardware.h"
#include <QObject>
#include <QThread>
#include <qthread.h>
using namespace std;
#include "ram.h"


int Hardware::getUsage()
{

}

void Hardware::getUsageInThread(QThread &thread)
{
    QObject::connect(&thread, SIGNAL(started()), this, SLOT(getUsageSlot()));
}

void Hardware::stop()
{
    stopUsage = true;
}

Hardware::Hardware(QObject *parent())
{

}

void Hardware::getUsageSlot()-
{
    while(!stopUsage)
    {
        QThread::sleep(1000);
        int currentUsage = getUsage();
        emit getUsageSignal(currentUsage);
    }
}
