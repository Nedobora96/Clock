#include "mainclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainClock w;
    w.show();

    return a.exec();
}
