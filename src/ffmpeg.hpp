#ifndef __DEFINE_FFMPEG_HPP
#define __DEFINE_FFMPEG_HPP

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QApplication>
#include "ui_main.h"

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread();
    ~Thread();

protected:
    void run();
};

class Worker : public QObject
{
    Q_OBJECT

private:
    QProcess *process;
    pid_t pid;
public slots:
    void doWork();
    void deleteSelf();

signals:
    void resultReady(const QString &result);
};

class FFMPEG : public QObject
{
    Q_OBJECT
    Thread workerThread;
    Worker *worker;
    QWidget *widget;
    QApplication *app;
    Ui_PlazaOne *ui;
    bool on;
    bool warn;

public:
    FFMPEG(QApplication *app, Ui_PlazaOne *ui, QWidget *widget);
    void start();
    void stop();
    ~FFMPEG();
public slots:
    void handleResults(const QString &);
    void toggle();
    void dummySlider();
signals:
    void operate(const QString &);
};

#endif