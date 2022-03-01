#ifndef FILECOPIER_H
#define FILECOPIER_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <cstring>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#include "conwin.h"
#include "copy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileCopier; }
QT_END_NAMESPACE

using namespace std;

class FileCopier : public QMainWindow
{
    Q_OBJECT

public:
    FileCopier(QWidget *parent = nullptr);
    ~FileCopier();

private slots:
    void on_btn_start_clicked();
    void on_le_src_textChanged(const QString &str);
    void on_le_dst_textChanged(const QString &str);

private:
    // ui
    Ui::FileCopier *ui;
    // file path
    string src_path;
    string dst_path;
    //
};
#endif // FILECOPIER_H
