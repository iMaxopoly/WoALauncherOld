#ifndef FETCHER_H
#define FETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>

class fetcher : public QObject {
	Q_OBJECT
public:
	explicit fetcher(QObject *parent = nullptr);
	~fetcher() {};
	QByteArray worker(QString url);
	QString fetch_news();
	QString fetch_launcher_version();
	QStringList fetch_game_version();
	QByteArray fetch_launcher(QString);
	QByteArray fetch_game(QString);

signals:
	void signal_download_progress(qint64, qint64);

private:

};

#endif // FETCHER_H