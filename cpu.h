#ifndef CPU_H
#define CPU_H
#include <QObject>
#include <QThread>
#include "hardware.h"

class CPU : public Hardware
{
    //Q_OBJECT

public:
    int getUsage();
    int getProcessUsage(int procHandler);
    //void getUsageInThread(QThread &thread);
    //void getProcessUsageInThread(QThread &cpuThread, int processID);
    //void stop();

    CPU();

public slots:
    //void getUsageSlot();
    void getProcessUsageSlot();

signals:
    //void getUsageSignal(int);
    void getProcessUsageSignal(int);

private:
    //bool stopUsage = false;
    int processID;
};

#endif // CPU_H
