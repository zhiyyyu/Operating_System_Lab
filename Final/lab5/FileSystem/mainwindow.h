#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstring>

#include "register.h"

using namespace std;

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
    void on_btn_register_clicked();

    void on_btn_login_clicked();

    void on_btn_exit_clicked();

private:
    Ui::MainWindow *ui;
    Register* reg;
    Register* login;
};
#endif // MAINWINDOW_H
