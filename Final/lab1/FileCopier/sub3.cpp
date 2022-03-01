#include "conwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConWin w(nullptr, "CPU");
    w.setWindowTitle("CPU Usage");
    w.show();
    return a.exec();
}
