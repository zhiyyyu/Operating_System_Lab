#include "system.h"
#include "ui_system.h"

System::System(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::System)
{
    ui->setupUi(this);
}

System::~System()
{
    delete ui;
}

void System::on_le_command_textChanged(const QString &arg1)
{
    command = arg1;
}

void System::on_btn_exec_clicked()
{
    if(command.isEmpty()){
        qDebug() << "input command.";
        return;
    }
    QStringList list = command.split(" ");
    if(list[0] == "mkdir"){
        qDebug() << "mkdir";
    } else if(list[0] == "rmdir"){

    } else if(list[0] == "cd"){

    } else if(list[0] == "ls"){

    } else if(list[0] == "readdir"){

    } else if(list[0] == "touch"){

    } else if(list[0] == "rm"){

    } else if(list[0] == "read"){

    } else if(list[0] == "write"){

    }
}

void System::on_command_textChanged(const QString &arg1)
{

}

void System::on_btn_help_clicked()
{

}

void System::on_btn_ok_clicked()
{
//    ui->content->
}

void System::on_content_textChanged()
{

}
