#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <QMainWindow>

namespace Ui {
class ParkingLot;
}

class ParkingLot : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParkingLot(QWidget *parent = nullptr);
    ~ParkingLot();

private:
    Ui::ParkingLot *ui;
};

#endif // PARKINGLOT_H