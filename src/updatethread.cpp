#include "updatethread.hpp.moc"
#include <QApplication>
#include <QTimer>
#include "ui_main.h"
#include "status.hpp"
#include "filedownloader.hpp"

UpdateThread::UpdateThread(QApplication *app, Ui_PlazaOne *ui)
{
    Status *status = new Status();

    this->app = app;
    this->ui = ui;
    this->status = status;

    this->updateStatus();
    this->updateMetadata();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimestamp()));
    timer->start(250);
}

void UpdateThread::updateStatus()
{
    this->status->update();
    while (!this->status->ready)
    {
        this->app->processEvents();
    }
}
void UpdateThread::updateMetadata()
{
    Song *song = this->status->song();
    QString title = song->artist();
    this->ui->songTitle->setText(title);

    this->ui->artistName->setText(song->title());

    QString image = song->artworkSource();
    new ImageSetter(this->ui->albumArt, image);
}

void UpdateThread::updateTimestamp()
{
    Song *song = this->status->song();

    int position = song->position();
    int song_length = song->length();

    if (position >= song_length)
    {
        this->updateStatus();
        this->updateMetadata();
    }
    int pos_minutes = position / 60;
    int pos_seconds = position - (60 * pos_minutes);

    int song_minutes = song_length / 60;
    int song_seconds = song_length - (60 * song_minutes);

    QString time = QString("%1:%2 / %3:%4")
                       .arg(pos_minutes, 2, 10, QChar('0'))
                       .arg(pos_seconds, 2, 10, QChar('0'))
                       .arg(song_minutes, 2, 10, QChar('0'))
                       .arg(song_seconds, 2, 10, QChar('0'));
    this->ui->timeRemaining->setText(time);
}