#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "log.h"
#include "demand.h"
#include "imfo.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include<vector>
#include<QString>
#include <vector>

void input(imfo i,int select);
void Initarray();
vector<vector<vector<imfo> > > coach(12, vector<vector<imfo> >(12, vector<imfo>(0)));
demand client(11,2,1);
extern int tmp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    //initTimeThread();
    Initarray();
    initConnect();
    on_resetTravelerInfo_clicked();
    enTimeBudget_Input();
    showTotalTime();
    showCurrentTime();

    //ui->RouteGraph_Output->setPixmap(QPixmap("D:/qt/qtxiangmu/test2/chinamap.jpg"));
    //QImage *image = new QImage("D:/qt/qtxiangmu/test2/chinamap.jpg");
    //ui->Picture->setPixmap(QPixmap::fromImage(image));
    //ui->TimeBudget_Input->setEnabled(false);
}

//初始化图形界面
void MainWindow::initUI()
{
     qDebug() << "Init UI succeed";
     this->setWindowTitle("旅行管理系统");
     /*QWidget *widget = new QWidget;
     widget->autoFillBackground(true);
     QPalette palette();
     palette().setBrush(QPalette::Background,QBrush(QPixmap("D:/qt/qtxiangmu/test2/chinamap.jpg")));
     widget->setPalette(palette);*/
}

//建立信号与槽
void MainWindow::initConnect()
{
    QObject::connect(ui->City0, SIGNAL(toggled(bool)), this, SLOT(setThroughCity0()));
    QObject::connect(ui->City1, SIGNAL(toggled(bool)), this, SLOT(setThroughCity1()));
    QObject::connect(ui->City2, SIGNAL(toggled(bool)), this, SLOT(setThroughCity2()));
    QObject::connect(ui->City3, SIGNAL(toggled(bool)), this, SLOT(setThroughCity3()));
    QObject::connect(ui->City4, SIGNAL(toggled(bool)), this, SLOT(setThroughCity4()));
    QObject::connect(ui->City5, SIGNAL(toggled(bool)), this, SLOT(setThroughCity5()));
    QObject::connect(ui->City6, SIGNAL(toggled(bool)), this, SLOT(setThroughCity6()));
    QObject::connect(ui->City7, SIGNAL(toggled(bool)), this, SLOT(setThroughCity7()));
    QObject::connect(ui->City8, SIGNAL(toggled(bool)), this, SLOT(setThroughCity8()));
    QObject::connect(ui->City9, SIGNAL(toggled(bool)), this, SLOT(setThroughCity9()));
    QObject::connect(ui->City10, SIGNAL(toggled(bool)), this, SLOT(setThroughCity10()));
    QObject::connect(ui->City11, SIGNAL(toggled(bool)), this, SLOT(setThroughCity11()));
}

//添加计时所用的线程和timer以确保时间计算的准确
/*void MainWindow::initTimeThread()
{
    //计时功能及所需的线程
    mstimer = new QTimer;
    mstimer->setInterval(1);

    timethread = new QThread();
    timethread->start();

    mstimer->moveToThread(timethread);
}*/

//单击“添加旅客”按钮，开始运行
void MainWindow::on_addTraveler_Click_clicked()
{
}

//获取旅客名称
void MainWindow::getTravelerName()
{
    TravelerName = ui->TravelerName_Input->text().toStdString();

}

//获取用户所选始发地
int MainWindow::getStart()
{

    return ui->Start_Select->currentIndex();
}

//获取用户所选目的地
int MainWindow::getDestination()
{
    return ui->End_Select->currentIndex();
}

//获取用户所选旅行模式
int MainWindow::getStrategy()
{
    return ui->Mode_Select->currentIndex();
}

//获取用户所选途经城市
/*void MainWindow::getThroughCity()
{

}*/

//获取出发时间范围_开始
int MainWindow::getTimeRange_Start()
{
    qDebug() << "Get TimeRange_Start";
    return ui->TimeRange_Start->currentIndex();
}

//获取出发时间范围_结束
int MainWindow::getTimeRange_End()
{
    qDebug() << "Get TimeRange_End";
    client.set_end_time(ui->TimeRange_End->currentIndex());
    return ui->TimeRange_End->currentIndex();
}

//获取早上/下午
int MainWindow::getAmPm_1()
{
    qDebug() << "Get AMPM_1";
    return ui->AmPm1->currentIndex();
}
int MainWindow::getAmPm_2()
{
    qDebug() << "Get AMPM_2";
    return ui->AmPm2->currentIndex();
}

//根据策略决定是否启用时间预算框
void MainWindow::enTimeBudget_Input()
{
    int currentStrategy = ui->Mode_Select->currentIndex();
    if(currentStrategy != 2)
        ui->TimeBudget_Input->setEnabled(false);
    else
        ui->TimeBudget_Input->setEnabled(true);
}

void MainWindow::on_Mode_Select_currentIndexChanged(int index)
{
    if(index != 2)
        ui->TimeBudget_Input->setEnabled(false);
    else
        ui->TimeBudget_Input->setEnabled(true);
}


//获取时间预算
void MainWindow::getTimeBudget()
{
    TimeBudget = ui->TimeBudget_Input->text().toStdString();
}


//显示旅客编号
void MainWindow::showTravelerNumber()
{
    ui->TravelerNumber_Output->setText("1");
}

//点击重置旅客信息/输入下一个旅客信息
void MainWindow::on_resetTravelerInfo_clicked()
{
    ui->TravelerName_Input->setText("");
    ui->Start_Select->setCurrentIndex(0);
    ui->End_Select->setCurrentIndex(0);
    ui->Mode_Select->setCurrentIndex(0);
    ui->City0->setChecked(false);
    ui->City1->setChecked(false);
    ui->City2->setChecked(false);
    ui->City3->setChecked(false);
    ui->City4->setChecked(false);
    ui->City5->setChecked(false);
    ui->City6->setChecked(false);
    ui->City7->setChecked(false);
    ui->City8->setChecked(false);
    ui->City9->setChecked(false);
    ui->City10->setChecked(false);
    ui->City11->setChecked(false);
    ui->TimeRange_Start->setCurrentIndex(0);
    ui->TimeRange_End->setCurrentIndex(0);
    ui->AmPm1->setCurrentIndex(0);
    ui->AmPm2->setCurrentText(0);
    ui->TimeBudget_Input->setText("");
    ui->TravelerNumber_Output->setText("000000");
    ui->TotalTime_Output->setText("0");
    ui->TotalFare_Output->setText("0");
    ui->TravelPath_Output->setText("");
    ui->TravelerNumber_Input->setText("");
    ui->Location_Output->setText("");
    ui->State_Output->setText("");
}


//点击生成旅行路线
void MainWindow::on_creatTravelPath_Click_clicked()
{
    client.set_departure(ui->Start_Select->currentIndex());
    client.set_arrival(ui->End_Select->currentIndex());
    client.set_strategy(ui->Mode_Select->currentIndex());
    client.set_start_time(ui->TimeRange_Start->currentIndex());
    client.least_money();

    ui->label->setNum(tmp);
    ui->TravelPath_Output->setText("000");
    ui->TravelerNumber_Output->setText("000");
}

//显示预计耗时
void MainWindow::showTotalTime()
{
    ui->TotalTime_Output->setText("48");
}

//显示预计费用
void MainWindow::showTotalFare()
{
    ui->TotalFare_Output->setText("4800");
}

//获取旅客编号
void MainWindow::getTravelerNumber()
{
    TravelerNumber = ui->TravelerNumber_Input->text().toStdString();
}

//点击开始查询
void MainWindow::on_startQuery_Click_clicked()
{
    ui->Location_Output->setText("北京");
    ui->State_Output->setText("火车");
}


//显示当前时间
void MainWindow::showCurrentTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString Currenttime_Str = time.toString("yyyy-MM-dd/h:00");
    ui->CurrentTime_Output->setText(Currenttime_Str);
}

//显示乘客当前所处地点
/*void MainWindow::showCurrentLocation()
{
    ui->Location_Output->setText("北京");
}

//显示乘客当前状态/乘坐交通工具
void MainWindow::showCurrentState()
{
    ui->State_Output->setText("火车");
}
*/
//退出图形界面
MainWindow::~MainWindow()
{
    qDebug() << "Program exit safely";
    //安全退出时间线程
    timethread->terminate();
    timethread->wait();
    delete ui;
    delete timethread;
}

//激活gridwidget中的checkbox并初始化throughcity
void MainWindow::activeThroughCity()
{
    ui->City0->setChecked(throughcity[0]);
    ui->City1->setChecked(throughcity[1]);
    ui->City2->setChecked(throughcity[2]);
    ui->City3->setChecked(throughcity[3]);
    ui->City4->setChecked(throughcity[4]);
    ui->City5->setChecked(throughcity[5]);
    ui->City6->setChecked(throughcity[6]);
    ui->City7->setChecked(throughcity[7]);
    ui->City8->setChecked(throughcity[8]);
    ui->City9->setChecked(throughcity[9]);
    ui->City10->setChecked(throughcity[10]);
    ui->City11->setChecked(throughcity[11]);
}

//设置12个城市哪些被指定途经
void MainWindow::setThroughCity0()
{
   if (ui->City0->isChecked())
       throughcity[0] = true;
   else
       throughcity[0] = false;
}
void MainWindow::setThroughCity1()
{
    if (ui->City1->isChecked())
        throughcity[1] = true;
    else
        throughcity[1] = false;
}
void MainWindow::setThroughCity2()
{
    if (ui->City2->isChecked())
        throughcity[2] = true;
    else
        throughcity[2] = false;
}
void MainWindow::setThroughCity3()
{
    if (ui->City3->isChecked())
        throughcity[3] = true;
    else
        throughcity[3] = false;
}
void MainWindow::setThroughCity4()
{
   if (ui->City4->isChecked())
       throughcity[4] = true;
   else
       throughcity[4]= false;
}
void MainWindow::setThroughCity5()
{
    if (ui->City5->isChecked())
        throughcity[5] = true;
    else
        throughcity[5] = false;
}
void MainWindow::setThroughCity6()
{
    if (ui->City6->isChecked())
        throughcity[6] = true;
    else
        throughcity[6] = false;
}
void MainWindow::setThroughCity7()
{
    if (ui->City7->isChecked())
        throughcity[7] = true;
    else
        throughcity[7] = false;
}
void MainWindow::setThroughCity8()
{
    if (ui->City8->isChecked())
        throughcity[8] = true;
    else
        throughcity[8] = false;
}
void MainWindow::setThroughCity9()
{
    if (ui->City9->isChecked())
        throughcity[9] = true;
    else
        throughcity[9] = false;
}
void MainWindow::setThroughCity10()
{
    if (ui->City10->isChecked())
        throughcity[10] = true;
    else
        throughcity[10] = false;
}
void MainWindow::setThroughCity11()
{
    if (ui->City11->isChecked())
        throughcity[11] = true;
    else
        throughcity[11] = false;
}
void input(imfo i,int select)
{
    int x=0, y=0;
    i.Set_type(select);
    //i.nametonum(x, y);
    if (strcmp(i.get_departure(),"长沙")==0)
    {
        x = 0;
    }
    if (strcmp(i.get_departure(),"沈阳")==0)
    {
        x = 1;
    }
    if (strcmp(i.get_departure(),"北京")==0)
    {
        x = 2;
    }
    if (strcmp(i.get_departure(),"石家庄")==0)
    {
        x = 3;
    }
    if (strcmp(i.get_departure(),"济南")==0)
    {
        x = 4;
    }
    if (strcmp(i.get_departure(),"西安") == 0)
    {
        x = 5;
    }
    if (strcmp(i.get_departure(),"杭州") == 0)
    {
        x = 6;
    }
    if (strcmp(i.get_departure(),"南昌") == 0)
    {
        x = 7;
    }
    if (strcmp(i.get_departure(),"武汉") == 0)
    {
        x = 8;
    }
    if (strcmp(i.get_departure(),"重庆") == 0)
    {
        x = 9;
    }
    if (strcmp(i.get_departure(),"广州") == 0)
    {
        x = 10;
    }
    if (strcmp(i.get_departure(),"南宁") == 0)
    {
        x = 11;
    }


    if (strcmp(i.get_arrival(),"长沙")==0)
    {
        y = 0;
    }
    if (strcmp(i.get_arrival(),"沈阳")==0)
    {
        y = 1;
    }
    if (strcmp(i.get_arrival(),"北京")==0)
    {
        y = 2;
    }
    if (strcmp(i.get_arrival(),"石家庄")==0)
    {
        y = 3;
    }
    if (strcmp(i.get_arrival(),"济南")==0)
    {
        y = 4;
    }
    if (strcmp(i.get_arrival(),"西安") == 0)
    {
        y = 5;
    }
    if (strcmp(i.get_arrival(),"杭州") == 0)
    {
        y = 6;
    }
    if (strcmp(i.get_arrival(),"南昌") == 0)
    {
        y = 7;
    }
    if (strcmp(i.get_arrival(),"武汉") == 0)
    {
        y = 8;
    }
    if (strcmp(i.get_arrival(),"重庆") == 0)
    {
        y = 9;
    }
    if (strcmp(i.get_arrival(),"广州") == 0)
    {
        y = 10;
    }
    if (strcmp(i.get_arrival(),"南宁") == 0)
    {
        y = 11;
    }
    coach[x][y].push_back(i);
    /*switch (select)
    {
    case 1:coach[x][y].push_back(i);
        break;
    case 2:air[x][y].push_back(i);
        break;
    case 3:train[x][y].push_back(i);
    default:
        break;
    }*/
}
void Initarray(){

    QFile file("H:/QT/untitled/bus.txt");

        QTextStream in(&file);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Write: open file error";
        return;
    }

    imfo a;
    int plus;
    while (!in.atEnd()) {
        QString departure,arrival,price,start,end,number;
        QString mText = in.readLine();

        QStringList city = mText.split("         ");
        departure = city.at(0);
        arrival = city.at(1);
        price = city.at(2);
        start =city.at(3);
        end = city.at(4);
        number = city.at(5);


        char str[30];
        char ch;
        //QString time;
        strcpy(str, departure.toStdString().data());
        a.Set_departure(str);
        strcpy(str, arrival.toStdString().data());
        a.Set_arrvial(str);
        a.Set_price(price.toFloat());
        a.Set_departure_time(start.toInt());
        strcpy(str, end.toStdString().data());
        ch=str[0];
        if (ch == '(')
                {
                    end = end.mid(4);
                    plus = ch - 39;
                    plus = plus * 24+end.toInt();

                    a.Set_arrival_time(plus);
                }
        else {
            a.Set_arrival_time(end.toInt());
        }

        a.Set_number(number.toStdString());

        input(a,1);

    }
}
