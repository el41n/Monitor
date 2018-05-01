#include "architectureproxy.h"

#include "family6arch.h"

ArchitectureProxy::ArchitectureProxy()
{
    setLeaf01H();
    switch(family)
    {
    case 6:
        pcArhitecture = new Family6Arch();
        pcArhitecture->setLeaf01H();
        //pcArhitecture->setLeaf01H();
        break;

    }
}

bool ArchitectureProxy::mapArchitecture()
{
    if(pcArhitecture->mapArchitecture())
    {

    }
}
