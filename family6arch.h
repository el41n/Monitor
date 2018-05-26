#ifndef FAMILY6ARCH_H
#define FAMILY6ARCH_H

class BigClientCores;
#include "architecture.h"
//#include "bigclientcores.h"


class Family6Arch : public Architecture
{
public:
    Family6Arch();
private:
    bool map6Architecture();
    Family6Arch *coreMicroArch;
    void setArch();
    //Family6Arch arch;
protected:
    bool mapArchitecture();
};

#endif // FAMILY6ARCH_H
