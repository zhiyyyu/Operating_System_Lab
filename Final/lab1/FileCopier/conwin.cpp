#include "conwin.h"
#include "ui_conwin.h"

ConWin::ConWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConWin)
{
    ui->setupUi(this);

    timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);
}

ConWin::ConWin(QWidget *parent, string key) :
    QMainWindow(parent),
    ui(new Ui::ConWin)
{
    ui->setupUi(this);
    ui->label->setText("pid");
    ui->label_2->setText(QString::number(getpid()));
    ui->key->setText(QString::fromStdString(key));
    this->key = key;
    timer = new QTimer (this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(1000);
}

ConWin::~ConWin()
{
    delete ui;
}

void ConWin::Update(){
    if(key == "Count"){
        ui->value->setText(QString::number(cnt++));
    } else if(key == "Timer"){
        QDateTime time =QDateTime::currentDateTime();
        QString time_str = time.toString("yyyy.MM.dd hh:mm:ss");
        ui->value->setText(time_str);
    } else{
        QProcess process;
        process.start("cat /proc/stat");
        process.waitForFinished();
        QString str = process.readLine();
        str.replace("\n","");
        str.replace(QRegExp("( ){1,}")," ");
//        cout << str.toStdString() << endl;

        auto lst = str.split(" ");
        if(lst.size() > 3)
        {
            double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
            double total = 0;
            for(int i = 1;i < lst.size();++i)
                total += lst[i].toDouble();
            if(total - m_cpu_total__ > 0)
            {
                usage = (use - m_cpu_use__) / (total - m_cpu_total__) * 100.0;
                ui->value->setText(QString::number(usage,'f',2)+"%");
                m_cpu_total__ = total;
                m_cpu_use__ = use;
            }
        }
    }
    return;
}
