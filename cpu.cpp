#include "cpu.h"
#include <exception>
#include <QObject>
#include <QThread>
#include <QDebug>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
    static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
#endif


int CPU::getUsage()
{
#ifdef _WIN32
    //sys times
    FILETIME idleTime;//waiting time
    FILETIME kernelTime;//exec kernel
    FILETIME userTime;//exec user progr
    //sys times for difference
    FILETIME idleTimeWaited;
    FILETIME kernelTimeWaited;
    FILETIME userTimeWaited;

    //getting times
    BOOL error = GetSystemTimes( &idleTime, &kernelTime, &userTime );
    if(error != ERROR_SUCCESS)
    {
        //throw exc
    }
    Sleep(1000);
    error = GetSystemTimes( &idleTimeWaited, &kernelTimeWaited, &userTimeWaited );
    if(error != ERROR_SUCCESS)
    {
        //throw std::system_error;
    }

    _ULARGE_INTEGER kernel;
    _ULARGE_INTEGER idle;
    _ULARGE_INTEGER user;

    _ULARGE_INTEGER kernel1;
    _ULARGE_INTEGER idle1;
    _ULARGE_INTEGER user1;
    //uses for calculate difference betwen two measures
    _ULARGE_INTEGER kernelDif;
    _ULARGE_INTEGER idleDif;
    _ULARGE_INTEGER userDif;

    _ULARGE_INTEGER sys;//time exec user and kernel
    _ULARGE_INTEGER cpu;//program time in percent
    _ULARGE_INTEGER prog;//time withoud idling

    kernel.HighPart = kernelTime.dwHighDateTime;
    kernel.LowPart = kernelTime.dwLowDateTime;
    idle.HighPart = idleTime.dwHighDateTime;
    idle.LowPart = idleTime.dwLowDateTime;
    user.HighPart = userTime.dwHighDateTime;
    user.LowPart = userTime.dwLowDateTime;

    kernel1.HighPart = kernelTimeWaited.dwHighDateTime;
    kernel1.LowPart = kernelTimeWaited.dwLowDateTime;
    idle1.HighPart = idleTimeWaited.dwHighDateTime;
    idle1.LowPart = idleTimeWaited.dwLowDateTime;
    user1.HighPart = userTimeWaited.dwHighDateTime;
    user1.LowPart = userTimeWaited.dwLowDateTime;

    kernelDif.QuadPart = kernel1.QuadPart - kernel.QuadPart;
    idleDif.QuadPart = idle1.QuadPart - idle.QuadPart;
    userDif.QuadPart = user1.QuadPart - user.QuadPart;

    sys.QuadPart = kernelDif.QuadPart + userDif.QuadPart;

    prog.QuadPart = sys.QuadPart - idleDif.QuadPart;

    cpu.QuadPart = prog.QuadPart * 100;

    cpu.QuadPart = int(cpu.QuadPart / sys.QuadPart);

    int cpu_int = int(cpu.QuadPart);
    return cpu_int;
#elif linux

    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }
    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return (int)percent;
}
#endif


//void CPU::stop()
//{
//    stopUsage = true;
//}

//void CPU::getUsageSlot()
//{
//    while(!stopUsage)
//    {
//        int currentUsage = getUsage();
//        emit getUsageSignal(currentUsage);
//    }
//}

//void CPU::getProcessUsageSlot()
//{
//    while(!stopUsage)
//    {
//        //Sleep(250);
//        int currentUsage = getProcessUsage(processID);
//        qDebug() << currentUsage;
//        emit getProcessUsageSignal(currentUsage);
//    }
//}

//void CPU::getUsageInThread(QThread &thread)
//{
//    connect(&thread, SIGNAL(started()), this, SLOT(getUsageSlot()));
//}

//void CPU::getProcessUsageInThread(QThread &cpuThread, int processID)
//{
//    connect(&cpuThread, SIGNAL(started()), this, SLOT(getProcessUsageSlot()));
//    this->processID = processID;
//}

int CPU::getProcessUsage(int procID)
{
#ifdef _WIN32
    //sys times
    FILETIME idleTime;//waiting timr
    FILETIME kernelTime;//exec kernel
    FILETIME userTime;//exec user progr
    //sys times for difference
    FILETIME idleTimeWaited;
    FILETIME kernelTimeWaited;
    FILETIME userTimeWaited;

    //getting times
    BOOL error = GetSystemTimes( &idleTime, &kernelTime, &userTime );
    if(error != ERROR_SUCCESS)
    {
        //throw exc
    }
    Sleep(250);
    error = GetSystemTimes( &idleTimeWaited, &kernelTimeWaited, &userTimeWaited );
    if(error != ERROR_SUCCESS)
    {
        //throw std::system_error;
    }

    _ULARGE_INTEGER kernel;
    _ULARGE_INTEGER user;

    _ULARGE_INTEGER kernel1;
    _ULARGE_INTEGER user1;
    //uses for calculate difference betwen two measures
    _ULARGE_INTEGER kernelDif;
    _ULARGE_INTEGER userDif;

    _ULARGE_INTEGER sys;//time exec user and kernel

    kernel.HighPart = kernelTime.dwHighDateTime;
    kernel.LowPart = kernelTime.dwLowDateTime;
    user.HighPart = userTime.dwHighDateTime;
    user.LowPart = userTime.dwLowDateTime;

    kernel1.HighPart = kernelTimeWaited.dwHighDateTime;
    kernel1.LowPart = kernelTimeWaited.dwLowDateTime;
    user1.HighPart = userTimeWaited.dwHighDateTime;
    user1.LowPart = userTimeWaited.dwLowDateTime;

    kernelDif.QuadPart = kernel1.QuadPart -  kernel.QuadPart;
    userDif.QuadPart = user1.QuadPart - user.QuadPart;

    sys.QuadPart = kernelDif.QuadPart + userDif.QuadPart;

    FILETIME procCreateTime;
    FILETIME procExitTime;
    FILETIME procKernelTime;
    FILETIME procUserTime;
    FILETIME procCreate1Time;
    FILETIME procExit1Time;
    FILETIME procKernel1Time;
    FILETIME procUser1Time;

    _ULARGE_INTEGER procKernel;
    _ULARGE_INTEGER procUser;
    _ULARGE_INTEGER procKernel1;
    _ULARGE_INTEGER procUser1;
    _ULARGE_INTEGER procPerf;

    _ULARGE_INTEGER procKernelDiff;
    _ULARGE_INTEGER procUserDiff;


    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
    if (processHandle == NULL)
    {
        ;
    }

    error = GetProcessTimes(processHandle, &procCreateTime, &procExitTime, &procKernelTime, &procUserTime);
    if(error != ERROR_SUCCESS)
    {
        //throw exc
    }
    Sleep(250);
    error = GetProcessTimes(processHandle, &procCreate1Time, &procExit1Time, &procKernel1Time, &procUser1Time);
    if(error != ERROR_SUCCESS)
    {
        //throw exc
    }

    procKernel.HighPart = procKernelTime.dwHighDateTime;
    procKernel.LowPart = procKernelTime.dwLowDateTime;

    procKernel1.HighPart = procKernel1Time.dwHighDateTime;
    procKernel1.LowPart = procKernel1Time.dwLowDateTime;

    procUser.HighPart = procUserTime.dwHighDateTime;
    procUser.LowPart = procUserTime.dwLowDateTime;

    procUser1.HighPart = procUser1Time.dwHighDateTime;
    procUser1.LowPart = procUser1Time.dwLowDateTime;

    procKernelDiff.QuadPart = procKernel1.QuadPart - procKernel.QuadPart;
    procUserDiff.QuadPart = procUser1.QuadPart - procUser.QuadPart;

    procPerf.QuadPart = procKernelDiff.QuadPart + procUserDiff.QuadPart * 100;
    procPerf.QuadPart = procPerf.QuadPart / sys.QuadPart;

    int cpu_usage = int(procPerf.QuadPart);
    return cpu_usage;
#endif
}

void CPU::init()
{
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
}

CPU::CPU() : Hardware(this)
{
#ifdef linux
    init();
#endif
}

