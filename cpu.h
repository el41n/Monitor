#ifndef CPU_H
#define CPU_H
#include <qobject.h>
#include <qthread.h>
#include "hardware.h"

class CPU : public QObject
{
    Q_OBJECT

public:
    int getUsage();
    int getProcessUsage(int procHandler);
    void getUsageInThread(QThread &cpuThread);
    void getProcessUsageInThread(QThread &cpuThread, int processID);
    void stop();

    explicit CPU(QObject *parent = 0);
    virtual ~CPU() {}

public slots:
    void getUsageSlot();
    void getProcessUsageSlot();

signals:
    void getUsageSignal(int);
    void getProcessUsageSignal(int);

private:
    bool stopUsage = false;
    int processID;
};

#endif // CPU_H
