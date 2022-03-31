#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // main page
    main_info = monitor->MainInfo();
    ui->host_name->setText(main_info[0]);
    ui->start_time->setText(main_info[1]);
    ui->run_time->setText(main_info[2]);
    ui->version->setText(main_info[3]);
    ui->CPU_info->setText(main_info[4]);
    on_btn_main_clicked();

    timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update(){
    // cpu
    QProcess process;
    process.start("cat /proc/stat");
    process.waitForFinished();
    QString str;
    str = process.readLine();
    auto lst = str.split(" ");
    double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
    double total = 0;
    for(int i = 1;i < lst.size();++i)
        total += lst[i].toDouble();
    if(total - cpu_total > 0)
    {
        cpu_usage = (use - cpu_use) / (total - cpu_total) * 100.0;
        ui->CPU_rate->setText(QString::number(cpu_usage,'f',2)+"%");
        cpu_total = total;
        cpu_use = use;
    }

    // mem
    process.start("cat /proc/meminfo");
    process.waitForFinished();
    str = process.readLine();
    QRegExp re("\\d+");
    re.indexIn(str, 0);
    total = re.cap(0).toDouble();
    str = process.readLine();
    re.indexIn(str, 0);
    use = re.cap(0).toDouble();
    mem_usage = (total - use) / total * 100;
    ui->Mem_rate->setText(QString::number(mem_usage,'f',2)+"%");

    // current time
    QDateTime time = QDateTime::currentDateTime();
    QString time_str = time.toString("yyyy.MM.dd hh:mm:ss");
    ui->Time->setText(time_str);
}

void MainWindow::on_btn_cpu_clicked()
{
    ui->stackedWidget->setCurrentIndex(CPU);
}

void MainWindow::on_btn_mem_clicked()
{
    ui->stackedWidget->setCurrentIndex(Mem);
}

void MainWindow::on_btn_proc_clicked()
{
    on_btn_all_clicked();
    ui->stackedWidget->setCurrentIndex(Proc);
}

void MainWindow::on_btn_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(Main);
}

void MainWindow::on_btn_pwroff_clicked()
{
    system("shutdown -s -t 0");
    return;
}

void MainWindow::on_le_pid_textChanged(const QString &str)
{
    pid = str;
}

void MainWindow::on_btn_search_clicked()
{
    if(pid.isEmpty()){
        qDebug() << "Input PID.";
        return;
    }
    QStringList list = Monitor::parseProcInfo(pid.toInt());
    if(list.empty()){
        qDebug() << "Not Existed.";
        return;
    }
    ui->ProcText->setText(list.join('\t'));
    pid = "";
}

void MainWindow::on_btn_all_clicked()
{
    QVector<QStringList>&& info = monitor->ProcInfo();
    QString procs;
    for(auto v: info){
        procs += v.join('\t') + '\n';
    }
    ui->ProcText->setText(procs);
}

void MainWindow::on_btn_kill_clicked()
{
    if(pid.isEmpty()){
        qDebug() << "Input PID.";
        return;
    }
    string command = "kill " + pid.toStdString();
    system(command.c_str());
    pid = "";
    on_btn_search_clicked();
    return;
}
