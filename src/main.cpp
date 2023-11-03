#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QTimer>

#include "ui_main.h"
#include "updatethread.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow widget;
    Ui::PlazaOne ui;
    ui.setupUi(&widget);

    // Volume icon
    QPixmap vol;
    vol.load("./ui/vol.png");
    ui.volumeIcon->setPixmap(vol);

    widget.show();

    new UpdateThread(&app, &ui);

    return app.exec();
}
