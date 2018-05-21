#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cpu.h"
#include "ram.h"
#include<QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setting sizes
    this->setFixedHeight(349);
    this->setFixedWidth(483);

    ui->vendor->setText(ax.getVendorMessage());

    ui->architecture->setText(ax.getMicroArchitecture());

    ui->coreType->setText(ax.getCore());

    ui->pcores->setText(QString::number(ax.getProcCores()));

    ui->L1D->setText(QString::number(ax.getCacheL1DataInfo() / 1024) + "KB");
    ui->L1I->setText(QString::number(ax.getCacheL1InstructionInfo() / 1024) + "KB");
    ui->L2->setText(QString::number(ax.getCacheL2Info() / 1024) + "KB");
    ui->L3->setText(QString::number(ax.getCacheL3Info() / 1024 / 1024) + "MB");

    ui->CPUpercent->setText("0%");
    //QThread cThread;

    cp.getUsageInThread(cpuThread);
    cp.moveToThread(&cpuThread);

    ram.getUsageInThread(ramThread);
    ram.moveToThread(&ramThread);

    //proc.getProcessUsageInThread(processThread, 6180);
    //proc.moveToThread(&processThread);

    cpuThread.start();
    ramThread.start();
    //processThread.start();

    ui->CPUProgressBar->setValue(0);

    connect(&cp, SIGNAL(getUsageSignal(int)), this, SLOT(numchange(int)));
    connect(&ram, SIGNAL(getUsageSignal(int)), this, SLOT(ramUsageChange(int)));
    //connect(&proc, SIGNAL(getProcessUsageSignal(int)), this, SLOT(procchange(int)));

    ui->CPUPlot->addGraph();
    ui->CPUPlot->xAxis->setRange(0, MAX_X_PLOT);
    ui->CPUPlot->yAxis->setRange(0, MAX_Y_PLOT);

    ui->RAMPlot->addGraph();
    ui->RAMPlot->xAxis->setRange(0, MAX_X_PLOT);
    ui->RAMPlot->yAxis->setRange(0, MAX_Y_PLOT);
}

MainWindow::~MainWindow()
{
    qDebug() << "im here";
    //QThread::finished();
    cp.stop();
    cpuThread.exit();
    cpuThread.wait();
    ram.stop();
    ramThread.exit();
    ramThread.wait();
    proc.stop();
    processThread.exit();
    processThread.wait();
    delete ui;
}

void MainWindow::numchange(int number)
{
    if (cpuUsageVector.size() == MAX_X_PLOT)
    {
        cpuUsageVector.removeFirst();
        cpuUsageVector.append(number);
    }
    else
    {
        cpuTimeVector.append(cpuUsageVector.size());
        cpuUsageVector.append(number);
    }
    ui->CPUPlot->graph(0)->setData(cpuTimeVector, cpuUsageVector);
    ui->CPUPlot->replot();

    ui->CPUProgressBar->setValue(number);
    ui->CPUpercent->setText("CPU\n"+QString::number(number)+"%");
}

void MainWindow::ramUsageChange(int number)
{
    if (ramUsageVector.size() == MAX_X_PLOT)
    {
        ramUsageVector.removeFirst();
        ramUsageVector.append(number);
    }
    else
    {
        ramTimeVector.append(cpuUsageVector.size());
        ramUsageVector.append(number);
    }
    ui->RAMPlot->graph(0)->setData(ramTimeVector, ramUsageVector);
    ui->RAMPlot->replot();

    ui->RAMProgressBar->setValue(number);
    ui->RamPercent->setText("RAM\n"+QString::number(number)+"%");
}

//void MainWindow::procchange(int number)
//{
//    ui->proclab->setText(QString::number(number)+"%");
//}
