#include "ram.h"
#include <QObject>
#include <QThread>

#ifdef _WIN32
#include "windows.h"
#include "psapi.h"
#endif


int RAM::getUsage()
{
#ifdef _WIN32
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&mem);
    DWORDLONG usedRAM = mem.ullTotalPhys - mem.ullAvailPhys;
    double ramUsage = (double)usedRAM / (double)mem.ullTotalPhys * 100;
    return (int)ramUsage;
#endif
}

RAM::RAM() : Hardware(this)
{

}
