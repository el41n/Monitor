#include "ram.h"
//using namespace std;
#include <QObject>
#include <QThread>
#include "windows.h"
#include "psapi.h"


int RAM::getUsage()
{
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&mem);
    DWORDLONG usedRAM = mem.ullTotalPhys - mem.ullAvailPhys;
    double ramUsage = (double)usedRAM / (double)mem.ullTotalPhys * 100;
    return (int)ramUsage;
}

//void RAM::getUsageInThread(QThread &thread)
//{
//    connect(&thread, SIGNAL(started()), this, SLOT(getUsageSlot()));
//}


//void RAM::getUsageSlot()
//{
//    while(!stopUsage)
//    {
//        Sleep(1000);
//        int currentUsage = getUsage();
//        emit getUsageSignal(currentUsage);
//    }

//}

//void RAM::stop()
//{
//    stopUsage = true;
//}

RAM::RAM(QObject *parent)
{

}
