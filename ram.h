#ifndef RAM_H
#define RAM_H
#include <qobject.h>
#include <QThread>
#include "hardware.h"


class RAM : public Hardware
{
public:
    int getUsage();
    //void getUsageInThread(QThread &thread);
    //void stop();

    explicit RAM(QObject *parent = 0);
    virtual ~RAM() {};

public slots:
    //void getUsageSlot();

signals:
    //void getUsageSignal(int);

private:
    //bool stopUsage = false;
    int processID;
};

#endif // RAM_H
