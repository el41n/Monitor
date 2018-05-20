#include "family6arch.h"
#include "micarch.h"
#include "bigclientcores.h"

Family6Arch::Family6Arch()
{

}

bool Family6Arch::mapArchitecture()
{
    bcCore = new BigClientCores();

    if(bcCore->mapArchitecture())
    {
        this->setMicroArchitecture(bcCore->getMicroArchitecture());
        this->setCore(bcCore->getCore());
        return true;
    } else
    {
        this->setMicroArchitecture("Unknown");
        this->setCore("Unknown");
        return false;
    }

    delete bcCore;
}
