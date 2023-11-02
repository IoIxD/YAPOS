#include "status.hpp.moc"
#include <QHttpRequestHeader>
#include <QHttp>
#include <QUrl>
#include <iostream>

Status::Status()
{
    this->ready = false;
    this->http = new QHttp("ioi-xd.net");

    bool what = QObject::connect(this->http, SIGNAL(requestFinished(int, bool)), this, SLOT(onRequestFinished(int, bool)));
    if (!what)
    {
        std::cout << "Failed to make a connection to http::requestFinished(int, bool)" << std::endl;
        exit(1);
    }
    this->update();
}

void Status::update()
{
    QHttpRequestHeader header("GET", "/plazastatus.php");
    header.setValue("Host", "ioi-xd.net");
    this->http->request(header);
}

void Status::onRequestFinished(int id, bool error)
{
    QByteArray arr = http->readAll();
    std::cout << "finished. making json." << std::endl;
    this->json = new JSON(std::string(arr.constData(), arr.length()));
    std::cout << "made json." << std::endl;
    this->ready = true;
}