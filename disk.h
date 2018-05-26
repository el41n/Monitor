#ifndef DISK_H
#define DISK_H
#include "hardware.h"
#include <QVector>
#include <QString>

using namespace std;

class Disk : public Hardware
{
public:
    QVector<double> getUsage();
    static int getDiskAmount();
    QVector<QString> getDiskNames();
    Disk();
    ~Disk();
private:
    static void getDiskNames(int &bufSize, char** buf);
    static QVector<QString> diskNames;
#ifdef _WIN32
    static int objectNumber;
    QVector<wchar_t *> diskString;
    static QVector<QString> parseDisks(int bufSize, char* buf);
#endif
};

#endif // DISK_H
