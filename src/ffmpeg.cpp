
#include <QObject>
#include <QThread>
#include <QMessageBox>

#include "ffmpeg.hpp.moc"

#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <QApplication>
#include "ui_main.h"

Thread::Thread() {}
Thread::~Thread(){};

void Thread::run()
{
}

void Worker::doWork()
{
    this->process = new QProcess();
#ifdef WIN32
    this->process->start("ffplay.exe -nodisp -x 1 -y 1 -vn  http://radio.plaza.one/mp3_low");
#else
    this->process->start("ffplay -nodisp -x 1 -y 1 -vn  http://radio.plaza.one/mp3_low");
    fork();
    this->process->waitForFinished();

#endif
    QString result;
    emit resultReady(result);
}
void Worker::deleteSelf()
{
    if (this->process != NULL)
    {
        this->process->kill();
    }
}

void FFMPEG::toggle()
{
    if (this->on)
    {
        this->ui->playButton->setText("Play");
        this->stop();
    }
    else
    {
        this->ui->playButton->setText("Pause");
        this->start();
    }
    this->on = !this->on;
}

void FFMPEG::dummySlider()
{
    if (this->warn)
    {
        QMessageBox::about(this->widget, "Sorry", "The volume slider doesn't actually work since we're literally opening another program to play the music.\nYou'll have to use your operating system's volume control instead.");
        this->warn = false;
    }
}

FFMPEG::FFMPEG(QApplication *app, Ui_PlazaOne *ui, QWidget *widget)
{
    this->app = app;
    this->ui = ui;
    this->on = false;
    this->warn = true;
    this->widget = widget;

    connect(this->ui->playButton, SIGNAL(pressed()), this, SLOT(toggle()));
    connect(this->ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(dummySlider()));
}

void FFMPEG::start()
{
    Worker *worker = new Worker;

    this->worker = worker;

#ifdef WIN32
    // Windows is so so so very very silly :3 and when we create a process it doesn't block anything :3 because the planning for this OS was done in a day after Bill Gates saw the Macintosh and shat himself
    this->worker->doWork();
#else

    this->worker->moveToThread(&this->workerThread);
    bool one = connect(&this->workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    bool two = connect(&this->workerThread, SIGNAL(finished()), worker, SLOT(deleteSelf()));
    bool three = connect(&this->workerThread, SIGNAL(finished()), worker, SLOT(deleteLater())); // deleteLater is inherited.

    this->widget->activateWindow();
    this->workerThread.start();
#endif
}
void FFMPEG::stop()
{
    this->worker->deleteSelf();
    this->workerThread.exit();
    this->workerThread.quit();
    this->workerThread.wait();
}
FFMPEG::~FFMPEG()
{
    this->workerThread.quit();
    this->workerThread.wait();
}

void FFMPEG::handleResults(const QString &){};

/*
    char *args[] = {"-nodisp", "http://radio.plaza.one/ogg_low", 0};
    execv("ffplay", args);
*/
