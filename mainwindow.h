#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <cpu.h>

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
    void numchange(int number);
    void procchange(int number);

signals:
    // finishCPUGetUsage();

private:
    Ui::MainWindow *ui;
    void showCpu();

    QThread cpuThread;
    QThread processThread;
    CPU cp;
    CPU proc;
};

#endif // MAINWINDOW_H
