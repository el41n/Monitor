#ifndef HARDWARE_H
#define HARDWARE_H
#include <QThread>
#include <QObject>

class Hardware : public QObject
{
  Q_OBJECT

public:
    virtual QVector<double> getUsage();
    void getUsageInThread(QThread &thread);
    void stop();
    explicit Hardware(Hardware *_currentHardware, QObject *parent() = 0);
    virtual ~Hardware() {}
    //vurtual ~Hardware() {}
    //virtual int getTemperature();

public slots:
    void getUsageSlot();
    //void getProcessUsageSlot();

signals:
    void getUsageSignal(QVector<double>);
    //void getProcessUsageSignal(int);

private:
    Hardware *currentHardware;
    bool stopUsage = false;
};

#endif // HARDWARE_H
