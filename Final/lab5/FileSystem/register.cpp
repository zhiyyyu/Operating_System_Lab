#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::Register(QWidget *parent, string type) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->type = type;
    ui->btn_register->setText(QString::fromStdString(type));
}

Register::~Register()
{
    delete ui;
}

void Register::on_le_username_textChanged(const QString &str)
{
    username = str.toStdString();
}

void Register::on_le_password_textChanged(const QString &str)
{
    password = str.toStdString();
}

void Register::on_btn_register_clicked()
{
    if(username.empty() || password.empty()){
        qDebug() << "Please Input Username And Password.\n";
        return;
    }
    if(type == "Login"){
        user_login();
    } else{
        user_register();
    }
    return;
}

void Register::user_login(){
    if(users.find(username) == users.end()){
        qDebug() << "User Not Exsited.\n";
        return;
    } else if(users[username] != password){
        qDebug() << "Wrong Password.\n";
        return;
    }
    sys = new System();
    sys->show();
    username = "";
    password = "";
    qDebug() << "login successfully.\n";
    return;
}

void Register::user_register(){
    if(users.find(username) != users.end()){
        qDebug() << "User Exsits.\n";
        return;
    }
    users[username] = password;
    qDebug() << "register successfully.\n";
    return;
}
