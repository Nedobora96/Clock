#include "mainclock.h"
#include "ui_mainclock.h"
#include <QString>
#include <QTime>

#include <QTimer>
#include "opcio.h"
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QMediaPlayer>

MainClock::MainClock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainClock)

{
    ui->setupUi(this);

    //int DayOfWeek = 0;

    ui->timeEdit->setTime(QTime::currentTime());
    ui->dateEdit->setDate(QDate::currentDate());

    this->setTrayIconActivations();
    this->showTrayIcon();

    timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timer_overflot()));
    timer->start(1000);
}

void MainClock::showTrayIcon(){

    trIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/Image/sony_ericsson.png");
    trIcon->setIcon(trayImage);
    trIcon->setContextMenu(trayIconMenu);

    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    trIcon->show();
}

void MainClock::trayActivationExecute(){

    QMessageBox::information(this,"TrayIco","Тестове повідомленння");
}

void MainClock::trayIconActivated(QSystemTrayIcon::ActivationReason reason){

    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->trayActivationExecute();
        break;
    default:
        break;
    }
}

void MainClock::setTrayIconActivations(){
    minimizeAction = new QAction("Звернути",this);
    restoreAction = new QAction("Востановити",this);
    quitAction = new QAction("Quit",this);

    connect(minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));
    connect(restoreAction,SIGNAL(triggered()),this,SLOT(showNormal()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(quit()));

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
}

void MainClock::quit(){
    QApplication::quit();
}

void MainClock::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if(event->type()==QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            this->hide();
        }
    }
}

void MainClock::StartAlarm(int i){

    ui->label->setText("Hello!");
    if(file[ui->spinBox->value()]!=""){
       // QMediaPlayer musicAlarm;
        //musicAlarm.setMedia(QUrl::fromLocalFile(file[i]));
        musicAlarm.setMedia(QUrl::fromLocalFile("E:\\2.mp3"));
        musicAlarm.setVolume(70);
        musicAlarm.play();
    }
    if(prog[ui->spinBox->value()]!=""){
        QString program = prog[ui->spinBox->value()];
        QStringList arguments;
        arguments << "-style" << "fusion";

        QProcess *myProcess = new QProcess(parent);
        myProcess->start(program, arguments);
    }


}

void MainClock::timer_overflot(){
    //ui->spinBox->setValue(DayOfWeek);
    ui->label->setText(QTime::currentTime().toString());
    for(int i=1;i<=9;i++){
    if(QTime::currentTime().toString()==alarma[i]){
        if(QDate::currentDate()==curda[i]) {
            StartAlarm(i);
        }
        for(int j = 0;j<8;j++){
        if(QDate::currentDate().dayOfWeek()==DayOfWeek[i][j]){
            StartAlarm(i);

        }
        }
    }
    }
    for(int i=1;i<=99;i++){
        if(timer_set[i]>=0){
        if(timer_set[i]==1){
            StartAlarm(i);
            timer_set[i]--;
        } else {
            timer_set[i]--;
        }

    }}


}

MainClock::~MainClock()
{
    delete ui;
    //delete musicAlarm;
    delete trIcon;
    delete trayIconMenu;
    delete minimizeAction;
    delete restoreAction;
    delete quitAction;
    delete parent;


}

void MainClock::on_pushButton_clicked()
{

    alarma[ui->spinBox->value()]=ui->timeEdit->time().toString();
    curda[ui->spinBox->value()] = ui->dateEdit->date();
    //ui->spinBox->setValue(QDate::currentDate().dayOfWeek());
    if(ui->checkFri->isChecked()) DayOfWeek[ui->spinBox->value()][5] = 5;
    else DayOfWeek[ui->spinBox->value()][5] = 0;
    if(ui->checkMon->isChecked()) DayOfWeek[ui->spinBox->value()][1] = 1;
    else DayOfWeek[ui->spinBox->value()][1] = 0;
    if(ui->checkTues->isChecked()) DayOfWeek[ui->spinBox->value()][2] = 2;
    else DayOfWeek[ui->spinBox->value()][2] = 0;
    if(ui->checkWednes->isChecked()) DayOfWeek[ui->spinBox->value()][3] = 3;
    else DayOfWeek[ui->spinBox->value()][3] = 0;
    if(ui->checkThurs->isChecked()) DayOfWeek[ui->spinBox->value()][4] = 4;
    else DayOfWeek[ui->spinBox->value()][4] = 0;
    if(ui->checkSatur->isChecked()) DayOfWeek[ui->spinBox->value()][6] = 6;
    else DayOfWeek[ui->spinBox->value()][6] = 0;
    if(ui->checkSun->isChecked()) DayOfWeek[ui->spinBox->value()][7] = 7;
    else DayOfWeek[ui->spinBox->value()][7] = 0;

}
//Вибір Музики
void MainClock::on_pushButton_2_clicked()
{
    file[ui->spinBox->value()] = QFileDialog::getOpenFileName(this,tr("Select Music"));
    if(file[ui->spinBox->value()]!=""){
        ui->pushButton->setEnabled(true);
    }
    ui->TestLocal->setText(file[ui->spinBox->value()]);
}

void MainClock::on_pushButton_3_clicked()
{
    musicAlarm.stop();
}

void MainClock::on_spinBox_valueChanged(const QString &arg1)
{
    if(file[ui->spinBox->value()]!=""){
        ui->pushButton->setEnabled(true);
    } else {
        ui->pushButton->setEnabled(false);
    }
    if(DayOfWeek[ui->spinBox->value()][5] == 5) ui->checkFri->setChecked(true);
    else ui->checkFri->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][1] == 1) ui->checkMon->setChecked(true);
    else ui->checkMon->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][2] == 2) ui->checkTues->setChecked(true);
    else ui->checkTues->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][3] == 3) ui->checkWednes->setChecked(true);
    else ui->checkWednes->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][4] == 4) ui->checkThurs->setChecked(true);
    else ui->checkThurs->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][6] == 6) ui->checkSatur->setChecked(true);
    else ui->checkSatur->setChecked(false);
    if(DayOfWeek[ui->spinBox->value()][7] == 7) ui->checkSun->setChecked(true) ;
    else ui->checkSun->setChecked(false);

}

void MainClock::on_pushButton_4_clicked()
{
    prog[ui->spinBox->value()] = QFileDialog::getOpenFileName(this,tr("Select Program"));
    if(prog[ui->spinBox->value()]!=""){
        ui->pushButton->setEnabled(true);
    }
}

void MainClock::on_TimerButton_clicked()
{
    timer_set[ui->TimerNum->value()]=ui->TimerSec->value();
}

void MainClock::on_pushButton_5_clicked()
{
    QMediaPlayer p;
    p.setMedia(QUrl::fromLocalFile("D:\2.mp3"));
    p.setVolume(70);
    p.play();
}
