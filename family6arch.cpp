#include "family6arch.h"
#include "micarch.h"
#include "bigclientcores.h"
#include "bigservercores.h"
#include "littlecores.h"
#include "micarchitecture.h"

Family6Arch::Family6Arch()
{

}

void Family6Arch::setArch()
{
    this->setMicroArchitecture(coreMicroArch->getMicroArchitecture());
    this->setCore(coreMicroArch->getCore());
}

bool Family6Arch::mapArchitecture()
{
    coreMicroArch = new BigClientCores();
    if(coreMicroArch->mapArchitecture())
    {
        setArch();
        return true;
    }
    delete coreMicroArch;
    coreMicroArch = new BigServerCores();
    {
        setArch();
        return true;
    }
    delete coreMicroArch;
    coreMicroArch = new LittleCores();
    {
        setArch();
        return true;
    }
    delete coreMicroArch;
    coreMicroArch = new MICArchitecture();
    {
        setArch();
        return true;
    }
    delete coreMicroArch;
    return false;
}
