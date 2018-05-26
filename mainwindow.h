#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <cpu.h>
#include "architectureproxy.h"
#include <ram.h>
#include "disk.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void cpuUsageChange(QVector<double>);
    void ramUsageChange(QVector<double>);
    void diskUsageChange(QVector<double>);
    //void procchange(int number);

signals:
    // finishCPUGetUsage();

private:
    Ui::MainWindow *ui;
    void showCpu();

    ArchitectureProxy ax;

    QThread cpuThread;
    QThread ramThread;
    QThread processThread;
    CPU cp;
    RAM ram;
    Disk disk;
    QThread diskThread;

    QVector<double> cpuUsageVector;
    QVector<double> ramUsageVector;
    QVector<double> cpuTimeVector;
    QVector<double> ramTimeVector;
    const int MAX_X_PLOT = 60;
    const int MAX_Y_PLOT = 100;
};

#endif // MAINWINDOW_H
