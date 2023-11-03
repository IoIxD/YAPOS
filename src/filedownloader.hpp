#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QUrl>
#include <QLabel>
#include <QHttp>
#include <QString>

class ImageSetter : public QObject
{
    Q_OBJECT
private:
    QHttp *http;
    QLabel *label;

public slots:
    void onRequestFinished(int id, bool error);

public:
    ImageSetter(QLabel *label, QString url);
    ~ImageSetter(){};
};

#endif // FILEDOWNLOADER_H
