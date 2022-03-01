#include "filecopier.h"
#include "./ui_filecopier.h"

FileCopier::FileCopier(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FileCopier)
{
    ui->setupUi(this);
//    connect(ui->btn_start,SIGNAL(clicked()),this,SLOT(on_btn_start_clicked()));
}

FileCopier::~FileCopier()
{
    delete ui;
}

void FileCopier::on_btn_start_clicked()
{
    if(src_path.empty() || dst_path.empty()){
        cout << "Need Src And Dst Path" << endl;
        return;
    }
    cout << "src: " << src_path << ", dst: " << dst_path << endl;
    return;
}

void FileCopier::on_le_src_textChanged(const QString &str)
{
    src_path = str.toStdString();
    return;
}

void FileCopier::on_le_dst_textChanged(const QString &str)
{
    dst_path = str.toStdString();
    return;
}

