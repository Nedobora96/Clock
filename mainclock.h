#ifndef MAINCLOCK_H
#define MAINCLOCK_H

#include <QMainWindow>
#include <QTimer>
#include <QDate>
//#include <phonon/AudioOutput>
//#include <phonon/MediaObject>
#include <QMediaObject>
#include <QMediaPlayer>
#include <QSystemTrayIcon>
#include <QProcess>

namespace Ui {
class MainClock;
}

class MainClock : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainClock(QWidget *parent = 0);
    QTimer *timer;
    QString alarma[99];
    QDate   curda[99];
    QString file[99];
    QString prog[99];
    int     timeOver[99];
    int     timer_set[99];

    QMediaPlayer musicAlarm;
    int DayOfWeek[99][7];


    ~MainClock();
public slots:
    void timer_overflot();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //void showHide(QSystemTrayIcon::ActivationReason);

    void on_spinBox_valueChanged(const QString &arg1);

    void StartAlarm(int i);

    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActivationExecute();
    void setTrayIconActivations();
    void showTrayIcon();
    void quit();

    void on_pushButton_4_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_TimerButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainClock *ui;

    QSystemTrayIcon *trIcon;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QObject *parent;
    QProcess *myProcess;



};

#endif // MAINCLOCK_H
