#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QDebug>
#include <string>
#include <unordered_map>

#include "system.h"

using namespace std;

static unordered_map<string, string> users;

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    explicit Register(QWidget *parent = nullptr, string type = nullptr);
    ~Register();

private slots:
    void on_le_username_textChanged(const QString &);
    void on_le_password_textChanged(const QString &);
    void on_btn_register_clicked();

private:
    void user_register();
    void user_login();

private:
    Ui::Register *ui;
    string type;
    string username;
    string password;
    System* sys;
};

#endif // REGISTER_H
