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
int numInF = 0;
int numInS = 0;
int waitingCar = 0;
int col = 0;
int col2 = 0;
int col3 = 0;
int pos = 0;

ParkingLot::ParkingLot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParkingLot)
{
    ui->setupUi(this);
    ui->Capacity->setText("10");
    ui->Waiting->setText("0");
}
ParkingLot::~ParkingLot()
{
    delete ui;
}

void ParkingLot::on_CarIn_clicked()
{
    if (carNum < 10 && numInF < 5){
        //入库车辆数加一
        carNum++;
        //获取车辆入库时间
        QTime inTime = QTime::currentTime();

        //创建代表车辆的按钮
        QPushButton *carBut = new QPushButton;
        QString temp = QString::number(car);
        car++;
        carBut->setObjectName(temp+"1");
        QIcon carIcon(":/carPic/car2.jpg");
        carBut->setMinimumSize(94,110);
        carBut->setMaximumSize(94,110);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());
        ui->FG->addWidget(carBut,0,col,1,1);
        col++;
        ui->FG->setColumnStretch(col,1);
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp+"1",inTime);
        numInF++;
    }

    else if (carNum < 10 && numInS < 5) {
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
        carBut->setMinimumSize(94,110);
        carBut->setMaximumSize(94,110);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());
        ui->SG->addWidget(carBut,0,col2,1,1);
        col2++;
        ui->SG->setColumnStretch(col2,1);
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp+"2",inTime);
        numInS++;
    }

    else if (carNum >= 10 && queue.size() < 5) {
        //创建代表车辆的按钮
        QPushButton *carBut = new QPushButton;
        QString temp = QString::number(car);
        car++;
        carBut->setObjectName(temp);
        carBut->setMinimumSize(94,110);
        carBut->setMaximumSize(94,110);
        QIcon icon(":/carPic/car.jpg");
        carBut->setIcon(icon);
        carBut->setIconSize(carBut->size());

        ui->WaitingRow->addWidget(carBut);

        //将待定车辆按钮加入等待队列
        queue.enqueue(carBut);
        waitingCar++;
        QString aux = QString::number(waitingCar);
        ui->Waiting->setText(aux);
    }



    else {
        //TODO: 弹出窗口提示车库和候车区均已满
    }
}


void ParkingLot::on_CarOut_clicked()
{
    //找到选中车辆并删除车辆按钮
    if (carNum >= 0){
        QWidget *w = new QWidget;
        w->setFixedSize(94,110);
        QPushButton *temp = ui->centralWidget->findChild<QPushButton*>(nowCar);
        if (nowCar.endsWith("1")){
            numInF--;
            ui->FG->replaceWidget(temp,w);
        }
        if (nowCar.endsWith("2")) {
            ui->SG->replaceWidget(temp,w);
            numInS--;
        }


        delete temp;
        carMes.remove(nowCar);
        carNum--;


        //判断候车队列是否有车
        if (queue.size() > 0){
            //入库车辆数加一
            carNum++;
            //获取车辆入库时间
            QTime inTime = QTime::currentTime();

            //从候车队列中获得优先等待的车辆按钮
            QPushButton *temp = queue.dequeue();
            QString ex_name = temp->objectName();

            if (nowCar.endsWith("1")){
                temp->setObjectName(ex_name+"1");
                QIcon carIcon(":/carPic/car2.jpg");
                temp->setIcon(carIcon);
                temp->setIconSize(temp->size());
                ui->FG->replaceWidget(w,temp);
                delete w;
                ui->WaitingRow->removeWidget(temp);
                numInF++;
            }

            if (nowCar.endsWith("2")){
                temp->setObjectName(ex_name+"2");
                QIcon carIcon(":/carPic/car.jpg");
                temp->setIcon(carIcon);
                temp->setIconSize(temp->size());
                ui->SG->replaceWidget(w,temp);
                delete w;
                ui->WaitingRow->removeWidget(temp);
                numInS++;
            }

            connect(temp,SIGNAL(clicked()),this,SLOT(message_check()));

            //将车辆信息加入QMap
            carMes.insert(temp->objectName(),inTime);
            waitingCar--;
            QString aux = QString::number(waitingCar);
            ui->Waiting->setText(aux);

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
    QString cur_fee = QString::number(fee);
    ui->Fee->setText(cur_fee);
}








