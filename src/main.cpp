#include <QApplication>
#include <QLabel>
#include <QPixmap>
#include "ui_main.h"
#include "status.hpp"

void getAndDisplayImage(QLabel *label)
{
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow widget;
    Ui::PlazaOne ui;
    ui.setupUi(&widget);

    // Get the image and display it.
    Status *status = new Status();

    widget.show();
    return app.exec();
}
