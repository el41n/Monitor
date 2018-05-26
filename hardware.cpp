#include "hardware.h"
#include <QObject>
#include <QThread>
#include <QDebug>
using namespace std;
#include "ram.h"


QVector<double> Hardware::getUsage()
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

Hardware::Hardware(Hardware *_currentHardware, QObject *parent())
{
    this->currentHardware = _currentHardware;
}

void Hardware::getUsageSlot()
{
    while(!stopUsage)
    {
        QThread::sleep(1);
        QVector<double> currentUsage = this->currentHardware->getUsage();
        emit getUsageSignal(currentUsage);
    }
}
