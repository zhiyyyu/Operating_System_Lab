#include "filecopier.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    if(int s1 = fork(); s1 == 0){
        execv("./sub1", argv);
        exit(0);
    }
    if(int s2 = fork(); s2 == 0){
        execv("./sub2", argv);
        exit(0);
    }
    if(int s3 = fork(); s3 == 0){
        execv("./sub3", argv);
        exit(0);
    }
    QApplication a(argc, argv);
    FileCopier w;
    w.setWindowTitle("Main");
    w.show();
    return a.exec();
}
