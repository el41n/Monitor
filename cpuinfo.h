#ifndef CPUINFO_H
#define CPUINFO_H

#include <QString>

class CPUInfo
{
public:

    QString vendorMessage();
    CPUInfo();
private:
    QString registerToMessage(unsigned int registerValue);
};

#endif // CPUINFO_H
