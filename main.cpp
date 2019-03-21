#include "parkinglot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParkingLot w;
    w.show();

    return a.exec();
}
