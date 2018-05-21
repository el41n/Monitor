#ifndef RAM_H
#define RAM_H
#include <qobject.h>
#include <QThread>
#include "hardware.h"


class RAM : public Hardware
{
public:
    int getUsage();
    RAM();

private:
    int processID;
};

#endif // RAM_H
