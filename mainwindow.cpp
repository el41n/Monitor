#include "mainwindow.h"
#include <GL/gl.h>
#include "ui_mainwindow.h"
#include "cpu.h"
#include "ram.h"
#include "disk.h"
#include<QThread>
#include <QDebug>
#include <QHeaderView>


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

    cp.getUsageInThread(cpuThread);
    cp.moveToThread(&cpuThread);

    ram.getUsageInThread(ramThread);
    ram.moveToThread(&ramThread);


    cpuThread.start();
    ramThread.start();

    ui->CPUProgressBar->setValue(0);

    connect(&cp, SIGNAL(getUsageSignal(QVector<double>)), this, SLOT(cpuUsageChange(QVector<double>)));
    connect(&ram, SIGNAL(getUsageSignal(QVector<double>)), this, SLOT(ramUsageChange(QVector<double>)));
    connect(&disk, SIGNAL(getUsageSignal(QVector<double>)), this, SLOT(diskUsageChange(QVector<double>)));

    ui->CPUPlot->addGraph();
    ui->CPUPlot->xAxis->setRange(0, MAX_X_PLOT);
    ui->CPUPlot->yAxis->setRange(0, MAX_Y_PLOT);

    ui->RAMPlot->addGraph();
    ui->RAMPlot->xAxis->setRange(0, MAX_X_PLOT);
    ui->RAMPlot->yAxis->setRange(0, MAX_Y_PLOT);

    int diskAmount = Disk::getDiskAmount();

    int colCount = 3;
    ui->diskTable->setRowCount(diskAmount);
    ui->diskTable->setColumnCount(colCount);
    ui->diskTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Disk name"));
    ui->diskTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Total space"));
    ui->diskTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Free space"));

    QVector<QString> diskNames = disk.getDiskNames();

    for(int i =0; i < diskAmount; i++)
    {
        ui->diskTable->setItem(i, 0, new QTableWidgetItem(diskNames[i]));
    }

    disk.getUsageInThread(diskThread);
    disk.moveToThread(&diskThread);
    diskThread.start();
}

MainWindow::~MainWindow()
{
    cp.stop();
    cpuThread.exit();
    cpuThread.wait();
    ram.stop();
    ramThread.exit();
    ramThread.wait();
    disk.stop();
    diskThread.exit();
    diskThread.wait();
//    proc.stop();
//    processThread.exit();
//    processThread.wait();
    delete ui;
}

void MainWindow::cpuUsageChange(QVector<double> number)
{
    if (cpuUsageVector.size() == MAX_X_PLOT)
    {
        cpuUsageVector.removeFirst();
        cpuUsageVector.append(number[0]);
    }
    else
    {
        cpuTimeVector.append(cpuUsageVector.size());
        cpuUsageVector.append(number[0]);
    }
    ui->CPUPlot->graph(0)->setData(cpuTimeVector, cpuUsageVector);
    ui->CPUPlot->replot();

    ui->CPUProgressBar->setValue(number[0]);
    ui->CPUpercent->setText("CPU\n"+QString::number(number[0])+"%");
}

void MainWindow::ramUsageChange(QVector<double> number)
{
    if (ramUsageVector.size() == MAX_X_PLOT)
    {
        ramUsageVector.removeFirst();
        ramUsageVector.append(number[0]);
    }
    else
    {
        ramTimeVector.append(cpuUsageVector.size());
        ramUsageVector.append(number[0]);
    }
    ui->RAMPlot->graph(0)->setData(ramTimeVector, ramUsageVector);
    ui->RAMPlot->replot();

    ui->RAMProgressBar->setValue(number[0]);
    ui->RamPercent->setText("RAM\n"+QString::number(number[0])+"%");
}

void MainWindow::diskUsageChange(QVector<double> number)
{
    for(int i=0; i < number.size(); i+=2)
    {
        if(number[i] < 0)
        {
            ui->diskTable->setItem(i/2, 2, new QTableWidgetItem("Unknown"));
            ui->diskTable->setItem(i/2, 1, new QTableWidgetItem("Unknown"));
            continue;
        }
        ui->diskTable->setItem(i/2, 2, new QTableWidgetItem(QString::number(number[i]) + " GB"));
        ui->diskTable->setItem(i/2, 1, new QTableWidgetItem(QString::number(number[i+1]) + " GB"));
    }
}
