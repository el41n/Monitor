#include "disk.h"
#ifdef _WIN32
#include <QVector>
#include "windows.h"
int Disk::objectNumber=0;
#elif linux
#include <mntent.h>
#include <sys/statvfs.h>
#endif
QVector<QString> Disk::diskNames;
#include <QDebug>
#include <QString>


QVector<double> Disk::getUsage()
{
#ifdef _WIN32
    _ULARGE_INTEGER freeSpace;
    _ULARGE_INTEGER totalSpace;
    _ULARGE_INTEGER totalFreeSpace;
    _ULARGE_INTEGER divisionNumber;
    divisionNumber.QuadPart = 1024*1024;

    QVector<double> usage;
    for(int i = 0; i < diskString.size(); i++)
    {
        int error = GetDiskFreeSpaceEx(diskString[i], &freeSpace, &totalSpace, &totalFreeSpace);
        if(error == 0)
        {
            usage.append(-1);
            usage.append(-1);
        }
        else
        {
            usage.append(freeSpace.QuadPart / (double)1024/1024/1024);
            usage.append(totalSpace.QuadPart / (double)1024/1024/1024);
        }
    }
    return usage;
#elif linux
    QVector<double> usage;
    struct statvfs str;
    for(int i =0; i < diskNames.size(); i++)
    {
        int error = statvfs(diskNames[i].toStdString().c_str(), &str);
        if(error != 0)
        {
            usage.append(-1);
            usage.append(-1);
        }
        else
        {
            usage.append(str.f_favail / (double)1024/1024/1024 * str.f_bsize);
            usage.append(str.f_blocks / (double)1024/1024/1024 * str.f_bsize);
        }
    }
    return usage;
#endif
}

int Disk::getDiskAmount()
{
#ifdef _WIN32
    if(diskNames.isEmpty())
    {
        int bufSize = 0;
        char **buf;
        getDiskNames(bufSize, buf);
        diskNames = parseDisks(bufSize, buf[0]);
        delete[] buf;
    }
    return diskNames.size();
#elif linux
    struct mntent *ent;
    FILE *aFile;
    diskNames.clear();

    aFile = setmntent("/proc/mounts", "r");
    if (aFile == NULL) {
      perror("setmntent");
      exit(1);
    }
    QString mountName;
    while (NULL != (ent = getmntent(aFile))) {
        mountName = ent->mnt_fsname;
        if(mountName.startsWith("/dev"))
        {
            mountName = ent->mnt_dir;
            qDebug() << ent->mnt_dir;
            diskNames.append(mountName);
        }
    }
    endmntent(aFile);
    return diskNames.size();
#endif
}

QVector<QString> Disk::getDiskNames()
{
    return diskNames;
}


Disk::Disk() : Hardware(this)
{
    if(diskNames.isEmpty())
    {
        getDiskAmount();
    }
#ifdef _win32
    diskString.clear();
    for(int i = 0; i < diskNames.size(); i++)
    {
        diskString.append(new wchar_t[diskNames[i].size()+1]);
        diskNames[i].toWCharArray(diskString[i]);
        diskString[i][diskNames[i].size()] = '\0';
    }
#elif linux

#endif
//    diskString = new wchar_t[diskNames[objectNumber].size()+1];
//    diskNames[objectNumber].toWCharArray(diskString);
//    diskString[diskNames[1].size()] = '\0';
//    objectNumber++;
}

Disk::~Disk()
{
    //delete diskString;
}

#ifdef _WIN32
void Disk::getDiskNames(int &bufSize, char **buf)
{
    int actualSize = GetLogicalDriveStringsA(bufSize, buf[0]);
    if (actualSize > bufSize)
    {
        //delete buf;
        bufSize = actualSize;
        *buf = new char[bufSize];
        GetLogicalDriveStringsA(bufSize, buf[0]);
    }
}

QVector<QString> Disk::parseDisks(int bufSize, char *buf)
{
    QVector<QString> diskNames;
    QString bufString;
    for(int i = 0; i < bufSize;)
    {
        while(buf[i] != '\0')
        {
            bufString.append(buf[i]);
            i++;
        }
        i++;
        if(bufString.isEmpty()) continue;
        diskNames.append(bufString);
        bufString.clear();
    }
    return diskNames;
}
#endif
