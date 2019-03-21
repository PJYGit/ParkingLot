#include "parkinglot.h"
#include "ui_parkinglot.h"
#include <QPushButton>
#include <QTime>
#include <QQueue>

QMap<QString,QTime> carMes;
QQueue<QPushButton*> queue;
int car = 1;
QString nowCar;
int carNum = 0;

ParkingLot::ParkingLot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParkingLot)
{
    ui->setupUi(this);
    ui->Capacity->setText("10");
}

ParkingLot::~ParkingLot()
{
    delete ui;
}

void ParkingLot::on_CarIn_clicked()
{

    if (carNum < 5){
        //入库车辆数加一
        carNum++;
        //获取车辆入库时间
        QTime inTime = QTime::currentTime();

        //创建代表车辆的按钮
        QPushButton *carBut = new QPushButton;
        QString temp = QString::number(car);
        car++;
        carBut->setObjectName(temp+"1");
        QIcon carIcon(":/carPic/car.jpg");
        carBut->setMinimumHeight(111);
        carBut->setMaximumHeight(111);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());
        ui->FirstRow->addWidget(carBut);
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp,inTime);
    }

    else if (carNum < 10 && carNum >= 5){
        //入库车辆数加一
        carNum++;
        //获取车辆入库时间
        QTime inTime = QTime::currentTime();

        //创建代表车辆的按钮
        QPushButton *carBut = new QPushButton;
        QString temp = QString::number(car);
        car++;
        carBut->setObjectName(temp+"2");
        QIcon carIcon(":/carPic/car.jpg");
        carBut->setMinimumHeight(111);
        carBut->setMaximumHeight(111);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());
        ui->SecondRow->addWidget(carBut);
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp,inTime);
    }

    else if (carNum >= 10 && queue.size() <= 5){
        //等待车辆数加一
        carNum++;
        //创建代表车辆的按钮
        QPushButton *carBut = new QPushButton;
        QString temp = QString::number(car);
        car++;
        carBut->setObjectName(temp);
        QIcon carIcon(":/carPic/car.jpg");
        carBut->setMinimumHeight(111);
        carBut->setMaximumHeight(111);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());

        //将待定车辆按钮加入等待队列
        queue.enqueue(carBut);
    }

    else {
        //TODO: 弹出窗口提示车库和候车区均已满
    }
}

void ParkingLot::on_CarOut_clicked()
{
    //找到选中车辆并删除车辆按钮
    if (carNum >= 0){
        QPushButton *temp = ui->centralWidget->findChild<QPushButton*>(nowCar);
        delete temp;
        carMes.remove(nowCar);
        carNum--;

        //判断候车队列是否有车
        if (queue.size() > 0){

            if (nowCar.endsWith("1")){
                //TODO: 在第一行车库中添加等待队列中的车辆，别忘记重新设置objectName
            }
            else if (nowCar.endsWith("2")){
                //TODO: 在第二行车库中添加等待队列中的车辆，别忘记重新设置objectName
            }

        }
    }

    else {//空车库，点击出库按钮时不进行任何操作
    }
}

void ParkingLot::message_check()
{
    //获取Sender的objectName
    QString temp = sender()->objectName();
    nowCar = temp;
    //获取入库时间与当前时间
    QTime in = carMes[temp];
    QString in_time = in.toString("hh:mm:ss");
    ui->InTime->setText(in_time);
    QTime cur = QTime::currentTime();
    QString cur_time = cur.toString("hh:mm:ss");
    ui->CurTime->setText(cur_time);

    //计算当前收费
    int fee = cur.hour()*3600+cur.minute()*60+cur.second() -
            in.hour()*3600-in.minute()*60-in.second();
    QString cur_fee = QString::number(fee*10);
    ui->Fee->setText(cur_fee);
}








