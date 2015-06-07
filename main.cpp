#include "timermain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimerMain w;
    w.show();

    return a.exec();
}
