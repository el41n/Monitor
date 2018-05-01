#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cpu.h"
#include<QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setting sizes
    this->setFixedHeight(300);
    this->setFixedWidth(400);

    ui->CPU->setText("Pars cpu");
    ui->CPUpercent->setText("0%");
    //QThread cThread;

    cp.getUsageInThread(cpuThread);
    cp.moveToThread(&cpuThread);

    proc.getProcessUsageInThread(processThread, 6180);
    proc.moveToThread(&processThread);

    cpuThread.start();
    processThread.start();

    ui->CPUProgressBar->setValue(0);

    connect(&cp, SIGNAL(getUsageSignal(int)), this, SLOT(numchange(int)));
    connect(&proc, SIGNAL(getProcessUsageSignal(int)), this, SLOT(procchange(int)));
}

MainWindow::~MainWindow()
{
    qDebug() << "im here";
    //QThread::finished();
    cp.stop();
    cpuThread.exit();
    cpuThread.wait();
    proc.stop();
    processThread.exit();
    processThread.wait();
    delete ui;
}

void MainWindow::numchange(int number)
{
    ui->CPUProgressBar->setValue(number);
    ui->CPUpercent->setText(QString::number(number)+"%");
}

void MainWindow::procchange(int number)
{
    ui->proclab->setText(QString::number(number)+"%");
}
