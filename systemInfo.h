#ifndef SYSTEM_H
#define SYSTEM_H
#include <qstring.h>
#include <windows.h>

class systemInformation
{
public:
    QString getProcessorArchitecture();
    int getPageGranularity();
    int getMinimumAppAddress();
    int getMaximumAppAdress();
    QString getProcessorType();

    void getProcID();
    void getProcInfo();

    void proba();

    systemInfo();
private:
    SYSTEM_INFO sysInfo;
};

#endif // SYSTEM_H
