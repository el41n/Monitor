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
    QVector<double> getTotalSpace();
    Disk();
    ~Disk();
private:
#ifdef _WIN32
    static int objectNumber;
    QVector<wchar_t *> diskString;
    static void getDiskNames(int &bufSize, char** buf);
    static QVector<QString> parseDisks(int bufSize, char* buf);
    static QVector<QString> diskNames;
    QVector<double> totalSpace;
#endif
};

#endif // DISK_H
