#include "filedownloader.hpp.moc"
#include <QHttp>
#include <QPixmap>

#include <iostream>
#include <string>

ImageSetter::ImageSetter(QLabel *label, QString url)
{
    this->http = new QHttp("ioi-xd.net");
    this->label = label;

    url = "/plaza/file.php?image=" + url;
    std::cout << "getting " << url.toStdString() << std::endl;

    QHttpRequestHeader header("GET", url);
    header.setValue("Host", "ioi-xd.net");
    this->http->request(header);

    bool what = QObject::connect(this->http, SIGNAL(requestFinished(int, bool)), this, SLOT(onRequestFinished(int, bool)));
    if (!what)
    {
        std::cout << "Failed to make a connection to http::requestFinished(int, bool)" << std::endl;
        exit(1);
    }
}
void ImageSetter::onRequestFinished(int id, bool error)
{

    std::cout << "request finished" << std::endl;
    QByteArray arr = http->readAll();

    QPixmap albumArt;
    albumArt.loadFromData(arr);
    this->label->setMargin(0);

    this->label->setPixmap(albumArt.scaled(111, 111));
}
