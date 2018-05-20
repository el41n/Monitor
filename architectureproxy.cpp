#include "architectureproxy.h"
#include "family4arch.h"
#include "family5arch.h"
#include "family6arch.h"

ArchitectureProxy::ArchitectureProxy()
{
    calculateProcToplogy();
    switch(family)
    {
    case 4:
        pcArhitecture = new Family4Arch();
        break;
    case 5:
        pcArhitecture = new Family5Arch();
        break;
    case 6:
        pcArhitecture = new Family6Arch();
        break;
    }

    pcArhitecture->calculateProcToplogy();
    pcArhitecture->calculateVendorMessage();
    pcArhitecture->mapArchitecture();
    pcArhitecture->calculateProcCores();
    pcArhitecture->calculateCacheInfo();
}

bool ArchitectureProxy::mapArchitecture()
{
    if(pcArhitecture->mapArchitecture())
    {

    }
}
