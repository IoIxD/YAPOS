#ifndef __SONG_HPP
#define __SONG_HPP
#include <string>
#include <QWidget>
#include <QHttp>
#include "time.h"

#include "json/json.hpp"

class Song
{
private:
	JSON *obj;
	time_t lastUpdated;
	int positionVal;

public:
	QString id() { return this->obj->getString("id"); }
	QString artist() { return this->obj->getString("artist"); }
	QString title() { return this->obj->getString("title"); }
	QString album() { return this->obj->getString("album"); }
	int length() { return (int)this->obj->getNumber("length"); }
	QString artworkSource() { return this->obj->getString("artwork_src"); }
	QString artworkSMSource() { return this->obj->getString("artwork_sm_src"); }
	int reactions() { return (int)this->obj->getNumber("reactions"); }

	int position(); // requires more then one line of code lmao

	Song(JSON *obj);
};
class Status : public QObject
{
	Q_OBJECT

private:
	QHttp *http;
	JSON *json;
	Song *songVal;

public slots:
	void onRequestFinished(int id, bool error);

public:
	bool ready;

	Status();
	virtual ~Status(){};

	void update();
	int listeners();
	int updatedAt();
	Song *song();
};

#endif
