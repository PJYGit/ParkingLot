#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <QMainWindow>
#include <QPushButton>
#include <QTime>
#include <QQueue>
#include <QMap>

namespace Ui {
class ParkingLot;
}

class ParkingLot : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParkingLot(QWidget *parent = nullptr);
    ~ParkingLot();
    void CarInAnimation(int xright);
    void CarOutAnimation(int xleft);
    void my_sleep();
    void CalculateCarWidth(int num);

private slots:
    void on_CarIn_clicked();
    void message_check();

    void on_CarOut_clicked();

private:
    Ui::ParkingLot *ui;
};

#endif // PARKINGLOT_H
