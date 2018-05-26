#ifndef CPU_H
#define CPU_H
#include <QObject>
#include <QThread>
#include "hardware.h"

class CPU : public Hardware
{
    //Q_OBJECT

public:
    QVector<double> getUsage();
#ifdef linux
    void init();
#endif
    CPU();
};


#endif // CPU_H
