#ifndef ARCHITECTUREPROXY_H
#define ARCHITECTUREPROXY_H

#include "architecture.h"

class ArchitectureProxy : public Architecture
{
public:
    ArchitectureProxy();
    bool mapArchitecture();
    QString getVendorMessage() { return pcArhitecture->getVendorMessage(); }
    QString getMicroArchitecture(){ return pcArhitecture->getMicroArchitecture(); }
    QString getCore() { return pcArhitecture->getCore();}
    unsigned int getProcCores() { return pcArhitecture->getProcCores(); }
    unsigned int getCacheL1DataInfo() { return pcArhitecture->getCacheL1DataInfo();}
    unsigned int getCacheL1InstructionInfo() { return pcArhitecture->getCacheL1InstructionInfo();}
    unsigned int getCacheL2Info() { return pcArhitecture->getCacheL2Info();}
    unsigned int getCacheL3Info() { return pcArhitecture->getCacheL3Info();}
private:
    Architecture *pcArhitecture;
};

#endif // ARCHITECTUREPROXY_H
