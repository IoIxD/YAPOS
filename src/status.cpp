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
}

void Status::onRequestFinished(int id, bool error)
{
    QByteArray arr = http->readAll();
    this->json = new JSON(std::string(arr.constData(), arr.length()));
    this->ready = true;
    JSONObject song = this->json->getObject("song");
    this->songVal = new Song(new JSON(song.serialize()));
}

void Status::update()
{
    QHttpRequestHeader header("GET", "/plaza/status.php");
    header.setValue("Host", "ioi-xd.net");
    this->http->request(header);
}

int Status::listeners()
{
    return (int)this->json->getNumber("listeners");
}
int Status::updatedAt()
{
    return (int)this->json->getNumber("updated_at");
}

Song *Status::song()
{
    return this->songVal;
}

Song::Song(JSON *obj)
{
    this->obj = obj;
    this->positionVal = (int)this->obj->getNumber("position");
    time(&this->lastUpdated);
}

int Song::position()
{
    time_t now;
    time(&now);
    return this->positionVal + (now - this->lastUpdated);
}