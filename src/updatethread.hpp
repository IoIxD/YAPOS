#ifndef __UPDATE_THREAD_HPP
#define __UPDATE_THREAD_HPP
#include <QApplication>
#include "ui_main.h"
#include "status.hpp"

class UpdateThread : public QObject
{
    Q_OBJECT
private:
    QApplication *app;
    Ui_PlazaOne *ui;
    Status *status;
    Song *song;

public slots:
    void updateStatus();
    void updateMetadata();
    void updateTimestamp();

public:
    UpdateThread(QApplication *app, Ui_PlazaOne *ui);
};
#endif