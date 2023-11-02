#ifndef __SONG_HPP
#define __SONG_HPP
#include <string>
#include <QWidget>
#include <QHttp>
#include "json.hpp"
class Song
{
public:
	std::string id;
	std::string artist;
	std::string title;
	std::string album;

	int position;
	int length;

	std::string artwork_src;
	std::string artwork_sm_src;
	int reactions;
};
class Status : public QObject
{
	Q_OBJECT

private:
	QHttp *http;
	JSON *json;
	int listeners;
	int updated_at;
	Song song;
	void update();

public slots:
	void onRequestFinished(int id, bool error);

public:
	bool ready;

	Status();
	virtual ~Status(){};
};

#endif
