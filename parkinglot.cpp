#include "parkinglot.h"
#include "ui_parkinglot.h"

ParkingLot::ParkingLot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParkingLot)
{
    ui->setupUi(this);
}

ParkingLot::~ParkingLot()
{
    delete ui;
}
