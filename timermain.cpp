#include "timermain.h"
#include "ui_timermain.h"
#include <QFile>
#include <cstdlib>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include <QDebug>

bool i = 0;

TimerMain::TimerMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimerMain)
{
    ui->setupUi(this);
}

TimerMain::~TimerMain()
{
    delete ui;
}

void TimerMain::on_OK_clicked()
{    
    i=1;
    int s = ui->Seconds->value();
    int m = ui->Minutes->value();
    int h = ui->hours->value();

    while(s>=60){
        s=s-60;
        m=m+1;
    }

    ui->Seconds->setValue(s);
    ui->Minutes->setValue(m);

    while(m>=60){
        m = m - 60;
        h=h+1;
    }
    ui->Minutes->setValue(m);
    ui->hours->setValue(h);

    int result = s + m*60 + h*60*60;
    ui->progressBar->setMaximum(result);

    QTime now = QTime::currentTime();
    QTime then(now.hour()+h, now.minute()+m, s);
    qDebug() << "Then has a value of " << then.toString();
    QString timeStr = then.toString();
    qDebug() << "timeStr has a value of " << timeStr << endl;
    QString title = "Shutdown at: " + timeStr;
    this->setWindowTitle(title);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(settime()));
    timer->start(1000);
}

void TimerMain::on_cancel_clicked()
{
    if(i==1)
        timer->stop();
    this->setWindowTitle("Timer");
}

void TimerMain::settime()
{
    int val = ui->progressBar->value();
    ui->progressBar->setValue(val+1);

    qDebug() << "Calling settime";
    int s = ui->Seconds->value();
    int m = ui->Minutes->value();
    int h = ui->hours->value();

    if((h==0) & (m==0) & (s==0))
        shutdown();
    if((s==0) & (m==0) & (h!=0)){
        ui->Seconds->setValue(59);
        ui->Minutes->setValue(59);
        ui->hours->setValue(h-1);
    }
    if((s==0) & (m!=0)){
        ui->Seconds->setValue(59);
        ui->Minutes->setValue(m-1);
    }
    if(s!=0)
        ui->Seconds->setValue(s-1);
}


void TimerMain::shutdown(){
    QString password;
    QString command = "echo " + password + " | sudo -S shutdown -h now";
    QFile script("azdf.sh");
    script.open(QIODevice::ReadWrite);
    QTextStream sout(&script);
    sout << "echo " + password + " | sudo -S shutdown -h now";
    system("sh azdf.sh");
}
void TimerMain::on_pushButton_clicked()
{
    close();
}

void TimerMain::on_Reset_clicked()
{
    ui->hours->setValue(0);
    ui->Minutes->setValue(0);
    ui->Seconds->setValue(0);
}
