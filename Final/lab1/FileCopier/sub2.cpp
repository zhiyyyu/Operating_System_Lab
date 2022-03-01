#include "conwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConWin w(nullptr, "Timer");
    w.setWindowTitle("Current Time");
    w.show();
    return a.exec();
}
