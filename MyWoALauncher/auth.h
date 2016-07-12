#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include <QtWebSockets/QtWebSockets>
#include <QCryptographicHash>
#include "diagnostics.h"
#include "preconf.h"

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class auth : public QObject
{
    Q_OBJECT
public:
    explicit auth(QObject *parent = nullptr);
	~auth() {};
	void dial(QString, QString);
	void shutting_down();
	signals:
	//local
	void signal_start_game(QString);
	//foreign
	void signal_disable_controls(bool);
	void signal_notify_ui_game_started();
	void signal_notify_ui_game_closed();
	void signal_send_tray_message(QString);
	void signal_send_status(QString);

public slots:	
	// Websocket slots
	void wss_onConnected();
	void wss_onDisconnected();
    void wss_onTextMessageReceived(QString message);
	void onSslErrors(const QList<QSslError> &errors);
	void wss_onError(QAbstractSocket::SocketError error);	
	// Local slots
	void slot_start_game(QString);
	void slot_collect_digest_post_game();

private:
	static std::string xor_encrypt(std::string toEncrypt);
	QNetworkRequest req;
	QWebSocket wss_socket;
	QString username, password, file_security_digest;
	QProcess *game_process;
};

#endif // AUTH_H