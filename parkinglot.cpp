#include "parkinglot.h"
#include "ui_parkinglot.h"
#include <QPushButton>
#include <QTime>
#include <QQueue>
#include <QStack>
#include <QPropertyAnimation>

QMap<QString,QTime> carMes;
QMap<QString,QString> carID;
QQueue<QPushButton*> queue;
QStack<QWidget*> wstack;
int car = 1;
QString nowCar;
int carNum = 0;
int numInF = 0;
int numInS = 0;
int waitingCar = 0;
int max = 10;
int first = 0;
int second = 0;
int carWidth = 94;

ParkingLot::ParkingLot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParkingLot)
{
    ui->setupUi(this);
    QString temp = QString::number(max);
    ui->Capacity->setText(temp);
    CalculateCarWidth(max);
    ui->Waiting->setText("0");
    wstack.push(nullptr);
}
ParkingLot::~ParkingLot()
{
    delete ui;
}

void ParkingLot::on_CarIn_clicked()
{
    if (wstack.top() != nullptr && wstack.top()->objectName() == "1"){

        CarInAnimation(wstack.top()->x()+110);


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
        carBut->setMinimumSize(carWidth,110);
        carBut->setMaximumSize(carWidth,110);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());

        ui->FG->replaceWidget(wstack.top(),carBut);
        QWidget *aux = wstack.top();
        wstack.pop();
        delete aux;
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp+"1",inTime);
        carID.insert(temp+"1",ui->IDin->toPlainText());
        numInF++;

    }

    else if (wstack.top() != nullptr && wstack.top()->objectName() == "2"){
        CarInAnimation(wstack.top()->x()+110);


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
        carBut->setMinimumSize(carWidth,110);
        carBut->setMaximumSize(carWidth,110);
        carBut->setIcon(carIcon);
        carBut->setIconSize(carBut->size());

        ui->SG->replaceWidget(wstack.top(),carBut);
        QWidget *aux = wstack.top();
        wstack.pop();
        delete aux;
        connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

        //将车辆信息加入QMap
        carMes.insert(temp+"2",inTime);
        carID.insert(temp+"2",ui->IDin->toPlainText());
        numInS++;
    }

    else if (wstack.top() == nullptr){

        if (carNum < max && numInF < first){
            CarInAnimation(110+numInF*carWidth);

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
            carBut->setMinimumSize(carWidth,110);
            carBut->setMaximumSize(carWidth,110);
            carBut->setIcon(carIcon);
            carBut->setIconSize(carBut->size());
            ui->FG->addWidget(carBut,0,numInF,1,1);

            ui->FG->setColumnStretch(numInF+1,1);
            connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

            //将车辆信息加入QMap
            carMes.insert(temp+"1",inTime);
            carID.insert(temp+"1",ui->IDin->toPlainText());
            numInF++;
        }

        else if (carNum < max && numInS < second) {
            CarInAnimation(110+numInS*carWidth);

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
            carBut->setMinimumSize(carWidth,110);
            carBut->setMaximumSize(carWidth,110);
            carBut->setIcon(carIcon);
            carBut->setIconSize(carBut->size());
            ui->SG->addWidget(carBut,0,numInS,1,1);

            ui->SG->setColumnStretch(numInS+1,1);
            connect(carBut,SIGNAL(clicked()),this,SLOT(message_check()));

            //将车辆信息加入QMap
            carMes.insert(temp+"2",inTime);
            carID.insert(temp+"2",ui->IDin->toPlainText());
            numInS++;
        }

        else if (carNum >= max && queue.size() < 5) {
            //创建代表车辆的按钮
            QPushButton *carBut = new QPushButton;
            QString temp = QString::number(car);
            car++;
            carBut->setObjectName(temp);
            carBut->setMinimumSize(carWidth,110);
            carBut->setMaximumSize(carWidth,110);
            QIcon icon(":/carPic/car.jpg");
            carBut->setIcon(icon);
            carBut->setIconSize(carBut->size());

            ui->WaitingRow->addWidget(carBut);

            //将待定车辆按钮加入等待队列
            queue.enqueue(carBut);
            waitingCar++;
            QString aux = QString::number(waitingCar);
            ui->Waiting->setText(aux);
            carID.insert(carBut->objectName(),ui->IDin->toPlainText());
        }

        else {
            //TODO: 弹出窗口提示车库和候车区均已满
        }
    }

    ui->IDin->setText("");
}


void ParkingLot::on_CarOut_clicked()
{
    //找到选中车辆并删除车辆按钮
    if (carNum > 0){

        QWidget *w = new QWidget;
        w->setFixedSize(carWidth,110);
        QPushButton *temp = ui->centralWidget->findChild<QPushButton*>(nowCar);
        int aux = temp->x()+110;
        if (nowCar.endsWith("1")){
            numInF--;
            ui->FG->replaceWidget(temp,w);
            w->setObjectName("1");
        }
        if (nowCar.endsWith("2")) {
            ui->SG->replaceWidget(temp,w);
            numInS--;
            w->setObjectName("2");
        }


        delete temp;
        carMes.remove(nowCar);
        carID.remove(nowCar);
        carNum--;

        CarOutAnimation(aux);



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
                CarInAnimation(w->x()+110);

                temp->setObjectName(ex_name+"1");
                QString aux = carID[ex_name];
                carID.remove(ex_name);
                carID.insert(ex_name+"1",aux);

                QIcon carIcon(":/carPic/car2.jpg");
                temp->setIcon(carIcon);
                temp->setIconSize(temp->size());
                ui->FG->replaceWidget(w,temp);
                delete w;
                ui->WaitingRow->removeWidget(temp);
                numInF++;
            }

            if (nowCar.endsWith("2")){
                CarInAnimation(w->x()+110);

                temp->setObjectName(ex_name+"2");
                QString aux = carID[ex_name];
                carID.remove(ex_name);
                carID.insert(ex_name+"2",aux);

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

        else if (queue.size() == 0){wstack.push(w);}


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
    QString id = carID[temp];
    ui->IDout->setText(id);

    //计算当前收费
    int fee = cur.hour()*3600+cur.minute()*60+cur.second() -
            in.hour()*3600-in.minute()*60-in.second();
    QString cur_fee = QString::number(fee);
    ui->Fee->setText(cur_fee);
}

void ParkingLot::CarInAnimation(int xright)
{
    QPushButton *temp = new QPushButton;

    QIcon carIcon(":/carPic/in.jpg");
    temp->setMinimumSize(111,carWidth);
    temp->setMaximumSize(111,carWidth);
    temp->setIcon(carIcon);
    temp->setIconSize(temp->size());

    ui->Road->addWidget(temp);

    QPropertyAnimation *animation = new QPropertyAnimation(temp, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(1,5,111,94));
    animation->setEndValue(QRect(xright,5,111,94));

    animation->start();
    my_sleep();
    delete temp;
    delete animation;
}

void ParkingLot::CarOutAnimation(int xleft)
{
    QPushButton *temp = new QPushButton;

    QIcon carIcon(":/carPic/out.jpg");
    temp->setMinimumSize(111,carWidth);
    temp->setMaximumSize(111,carWidth);
    temp->setIcon(carIcon);
    temp->setIconSize(temp->size());

    ui->Road->addWidget(temp);

    QPropertyAnimation *animation = new QPropertyAnimation(temp, "geometry");
    animation->setDuration(3000);
    animation->setStartValue(QRect(xleft,5,111,94));
    animation->setEndValue(QRect(1,5,111,94));

    animation->start();

    my_sleep();
    delete temp;
    delete animation;
}

//3秒延时函数
void ParkingLot::my_sleep()
{
    QTime reachTime = QTime::currentTime().addSecs(3);

    while (QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void ParkingLot::CalculateCarWidth(int num)
{
    int width = 141 - 4.7*num;
    carWidth = width;

    if (num % 2 == 0){
        first = second = num / 2;
    }
    else {
        first = (num + 1) / 2;
        second = (num - 1) / 2;
    }
}
























