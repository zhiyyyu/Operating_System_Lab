#ifndef SYSTEM_H
#define SYSTEM_H

#include <QMainWindow>
#include <QDebug>

//constexpr int STORAGE = 1024*1024;   //Byte

namespace Ui {
class System;
}

class System : public QMainWindow
{
    Q_OBJECT

public:
    explicit System(QWidget *parent = nullptr);
    ~System();

private slots:
    void on_le_command_textChanged(const QString &arg1);

    void on_btn_exec_clicked();

    void on_command_textChanged(const QString &arg1);

    void on_btn_help_clicked();

    void on_btn_ok_clicked();

    void on_content_textChanged();

private:
    Ui::System *ui;
    QString command;
};

#endif // SYSTEM_H
