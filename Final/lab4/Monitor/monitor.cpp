#include "monitor.h"

Monitor::Monitor(){

}

Monitor::~Monitor(){

}

void Monitor::CPUInfo(){

}

void Monitor::MemInfo(){

}

QVector<QStringList> Monitor::ProcInfo(){
    QDir dir("/proc");
    QRegExp proc_re("^\\d+$");
    QStringList list = dir.entryList();
    QVector<QStringList> info;
    for(auto it: list){
        if(proc_re.exactMatch(it)){
            info.push_back(parseProcInfo(it.toInt()));
        }
    }
    return info;
}

QStringList Monitor::parseProcInfo(int pid){
    QFile f("/proc/" + QString::number(pid) + "/stat");
    QStringList v;
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        return v;
    }
    QTextStream in(&f);
    QString line = in.readLine();
    auto list = line.split(' ');
    // pid name state ppid pri mem
    v.push_back(list[0]);
    v.push_back(list[1].mid(1, min(9, list[1].size()-2)));
    v.push_back(list[2]);
    v.push_back(list[3]);
    v.push_back(list[17]);
    v.push_back(list[22]);
    f.close();
    return move(v);
}

QVector<QString> Monitor::MainInfo(){
    QVector<QString> main_info;
    // hostname
    QFile f_host("/proc/sys/kernel/hostname");
    f_host.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_host(&f_host);
    QString host = in_host.readLine();
    main_info.push_back(host);
    f_host.close();

    // time
    QFile f_time("/proc/uptime");
    f_time.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_time(&f_time);
    QString time = in_time.readLine();
    main_info.push_back(time.left(time.indexOf(' ')));
    main_info.push_back(time.right(time.size() - 1 - time.indexOf(' ')));
    f_time.close();

    // OS
    QFile f_type("/proc/sys/kernel/ostype");
    f_type.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_type(&f_type);
    QString os = in_type.readLine();
    QFile f_version("/proc/sys/kernel/osrelease");
    f_version.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in_version(&f_version);
    os = os + " " + in_version.readLine();
    main_info.push_back(os);
    f_type.close();
    f_version.close();

    // CPU
    QFile f_cpu("/proc/cpuinfo");
    f_cpu.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&f_cpu);
    QString cpu;
    for(int _=0;_<5;_++) cpu = in.readLine();
    main_info.push_back(cpu.right(cpu.size() - cpu.indexOf(":") - 2));
    f_cpu.close();

    return main_info;
}
