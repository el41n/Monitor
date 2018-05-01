#ifndef GPU_H
#define GPU_H

#include "hardware.h"

class GPU : Hardware
{
public:
    int getUsage();
    GPU();
    ~GPU();
};

#endif // GPU_H
