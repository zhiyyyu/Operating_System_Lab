#ifndef CONWIN_H
#define CONWIN_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QProcess>
#include <cstring>
#include <unistd.h>
#include <iostream>

using namespace std;

namespace Ui {
class ConWin;
}

class ConWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConWin(QWidget *parent = nullptr);
    explicit ConWin(QWidget *parent = nullptr, string key = "");
    ~ConWin();

private slots:
    void Update();

private:
    Ui::ConWin *ui;
    QTimer* timer;
    int cnt = 0;
    string key;
    double m_cpu_total__;
    double m_cpu_use__;
    double usage;
};

#endif // CONWIN_H
