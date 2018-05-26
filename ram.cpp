#include "ram.h"
#include <QObject>
#include <QThread>
#include <QVector>

#ifdef _WIN32
#include "windows.h"
#include "psapi.h"
#elif linux
#include "sys/types.h"
#include "sys/sysinfo.h"
#endif


QVector<double> RAM::getUsage()
{
#ifdef _WIN32
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&mem);
    DWORDLONG usedRAM = mem.ullTotalPhys - mem.ullAvailPhys;
    double ramUsage = (double)usedRAM / (double)mem.ullTotalPhys * 100;
    QVector<double> usage;
    usage.append((int)ramUsage);
    return usage;
#elif linux
    struct sysinfo mem;
    sysinfo(&mem);
    long long memUsed = mem.totalram - mem.freeram;
    memUsed *= mem.mem_unit;
    memUsed = (double)memUsed / (double)mem.totalram * 100;
    QVector<double> usage;
    usage.append((int)memUsed);
    return usage;;
#endif
}

RAM::RAM() : Hardware(this)
{

}
