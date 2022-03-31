#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_register_clicked()
{
    reg = new Register(this, "Register");
    reg->show();
}

void MainWindow::on_btn_login_clicked()
{
    login = new Register(this, "Login");
    login->show();
}

void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}
