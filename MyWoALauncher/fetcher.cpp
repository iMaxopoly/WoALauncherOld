#include "preconf.h"
#include "fetcher.h"

fetcher::fetcher(QObject *parent) : QObject(parent) {
	
}

QByteArray fetcher::worker(QString url) {
	QNetworkAccessManager manager;
	QByteArray result;

	// Preparing Request with custom user agent
	QNetworkRequest request;
	request.setUrl(QUrl(url));
	request.setRawHeader("User-Agent", const_useragent);

	QNetworkReply *reply = manager.get(request);

	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	connect(reply, &QNetworkReply::downloadProgress,
		[=](qint64 read, qint64 total) {emit signal_download_progress(read, total); });
	loop.exec();
	if(reply->error() != QNetworkReply::NoError) {
		reply->deleteLater();
		qDebug() << reply->errorString();
		result = "";
	}else {
		result = reply->readAll();
	}	
	reply->deleteLater();
	return result;
}

QString fetcher::fetch_news() {
	auto result = QString(worker(const_game_news_url));
	qDebug() << result;
	return result;
}

QString fetcher::fetch_launcher_version() {
	auto result = QString(worker(const_launcher_version_url));
	qDebug() << result;
	return result;
}

QStringList fetcher::fetch_game_version() {
	auto result = QString(worker(const_game_version_url));
	qDebug() << result;
	return result.split(";");
}

QByteArray fetcher::fetch_launcher(QString url) {
	QByteArray result = worker(url);
	return result;
}

QByteArray fetcher::fetch_game(QString url) {
	QByteArray result = worker(url);
	return result;
}