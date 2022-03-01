#include "conwin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConWin w(nullptr, "Count");
    w.setWindowTitle("Count Frame");
    w.show();
    return a.exec();
}
