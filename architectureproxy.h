#ifndef ARCHITECTUREPROXY_H
#define ARCHITECTUREPROXY_H

#include "architecture.h"

class ArchitectureProxy : public Architecture
{
public:
    ArchitectureProxy();
    bool mapArchitecture();
    QString getMicroArchitecture(){ return pcArhitecture->getMicroArchitecture(); }
    QString getCore() { return pcArhitecture->getCore();}
private:
    Architecture *pcArhitecture;
};

#endif // ARCHITECTUREPROXY_H
