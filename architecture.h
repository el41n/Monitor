
#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

#include <QString>


class Architecture
{
public:
    void calculateVendorMessage();

    QString getMicroArchitecture();
    QString getCore();
    void setMicroArchitecture(QString newMicroArchitecture);
    void setCore(QString newCore);
    virtual bool mapArchitecture()=0;
    unsigned int getProcCores();
    unsigned int getCacheL1DataInfo();
    unsigned int getCacheL1InstructionInfo();
    unsigned int getCacheL2Info();
    unsigned int getCacheL3Info();

    void calculateProcToplogy();
    void calculateCacheInfo();
    void calculateProcCores();

    QString getVendorMessage();

protected:
    QString registerToMessage(unsigned int registerValue);
    int cores;
    unsigned int L1dataCache;
    unsigned int L1instructionCache;
    unsigned int L2cache;
    unsigned int L3cache;

    QString core;
    int extendedFamily;
    int extendedModel;
    int type;
    int family;
    int model;
    int stepping;
    QString microArchitecture;
    QString vendorMessage;
    bool matched;
};

#endif // ARCHITECTURE_H
