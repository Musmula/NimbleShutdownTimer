#ifndef TIMERMAIN_H
#define TIMERMAIN_H

#include <QMainWindow>

namespace Ui {
class TimerMain;
}

class TimerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimerMain(QWidget *parent = 0);
    ~TimerMain();

private slots:
    void on_OK_clicked();

    void on_cancel_clicked();

    void settime();
    void shutdown();

    void on_pushButton_clicked();

    void on_Reset_clicked();

private:
    Ui::TimerMain *ui;
    QTimer *timer;
};

#endif // TIMERMAIN_H
