#ifndef MONITOR_H
#define MONITOR_H

#include <QFile>
#include <QDebug>
#include <QVector>
#include <QDir>

//#include <utility>

using namespace std;

class Monitor
{
public:
    Monitor();
    ~Monitor();

 public:
    QVector<QString> MainInfo();
    void CPUInfo();
    void MemInfo();
    QVector<QStringList> ProcInfo();
    static QStringList parseProcInfo(int pid);

private:
    QString parseCPUInfo();

private:

};

#endif // MONITOR_H
