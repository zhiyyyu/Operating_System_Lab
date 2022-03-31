#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QProcess>
#include <QTime>
#include <QVector>

#include "monitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_cpu_clicked();

    void on_btn_mem_clicked();

    void on_btn_proc_clicked();

    void on_btn_main_clicked();

    void Update();

    void on_btn_pwroff_clicked();

    void on_le_pid_textChanged(const QString &arg1);

    void on_btn_search_clicked();

    void on_btn_all_clicked();

    void on_btn_kill_clicked();

private:
    Ui::MainWindow *ui;

    typedef enum Type {
        Main,
        CPU,
        Mem,
        Proc
    } Type;

    Monitor* monitor;
    QTimer* timer;
    QVector<QString> main_info;

    double cpu_total;
    double cpu_use;
    double cpu_usage;
    double mem_usage;

    QString pid;
};
#endif // MAINWINDOW_H
