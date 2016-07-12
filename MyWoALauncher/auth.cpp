#include "auth.h"

auth::auth(QObject* parent) : QObject(parent) {
	// Setting up Websockets
	connect(&wss_socket, &QWebSocket::connected, this, &auth::wss_onConnected);
	connect(&wss_socket, &QWebSocket::disconnected, this, &auth::wss_onDisconnected);
	connect(&wss_socket, static_cast<void(QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
		this, &auth::wss_onError);

	typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);
	connect(&wss_socket, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
		this, &auth::onSslErrors);
	connect(&wss_socket, &QWebSocket::textMessageReceived, this, &auth::wss_onTextMessageReceived);
	connect(this, SIGNAL(signal_start_game(QString)), this, SLOT(slot_start_game(QString)));

	req.setUrl(QUrl(const_ws_url));
	req.setRawHeader("User-Agent", const_useragent);
	game_process = new QProcess(this);

	// Signal Slot for game process on start and on exit
	connect(game_process, &QProcess::started, [=]() {
		emit signal_notify_ui_game_started();
		QTimer::singleShot(5000, this, SLOT(slot_collect_digest_post_game()));
	});
	connect(game_process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
		[=]() {
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_notify_ui_game_closed();
	});
	connect(game_process, &QProcess::errorOccurred, [=]() {
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_send_tray_message("Error encountered with game!");
		emit signal_disable_controls(false);
	});
}

void auth::dial(QString s_username, QString s_password) {
	if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
		return;
	}
	username = s_username;
	password = s_password;
	wss_socket.open(req);
}

void auth::shutting_down() {
	if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
		wss_socket.abort();
	}
	if(game_process->state() != QProcess::NotRunning) {
		game_process->close();
	}
}

void auth::wss_onConnected() {
	qDebug() << "WebSocket connected";
	auto digest = diagnostics::check_digest();
	QString SocketHash = QString::fromStdString(xor_encrypt(QString(username + "wind" + password + "wind" + digest).toStdString())).toLatin1().toHex();
	username.clear(); password.clear();
	wss_socket.sendTextMessage(SocketHash);
}

void auth::wss_onDisconnected() {
	qDebug() << "WebSocket disconnected";
	if(game_process->state() != QProcess::NotRunning) {
		game_process->close();
	}
	emit signal_send_status("Winds Of Arithia 2016");
	emit signal_disable_controls(false);
}

void auth::wss_onTextMessageReceived(QString message) {
	qDebug() << "Message received:" << message;
	if(message == conf_launcher_err_loginfail) {
		emit signal_send_tray_message("Wrong Username/Password, please try again!");
		emit signal_disable_controls(false);
		return;
	}
	if(!message.contains(conf_gamekey_salt) || !message.contains(";")) {
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_disable_controls(false);
		return;
	}
	auto temp = message.split(';');
	auto game_relevant = temp[0];
	file_security_digest = temp[1];
	if(diagnostics::check_digest() != file_security_digest) {
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_send_tray_message("Digest check failed, please contact support.");
		emit signal_disable_controls(false);
		return;
	}
	game_relevant.replace(conf_gamekey_salt, "");
	emit signal_start_game(game_relevant);
}

void auth::onSslErrors(const QList<QSslError>& errors) {
	Q_UNUSED(errors);

	// WARNING: Never ignore SSL errors in production code.
	// The proper way to handle self-signed certificates is to add a custom root
	// to the CA store.
	emit signal_send_tray_message("Unable to connect via a secure network layer");
	emit signal_disable_controls(false);
}

void auth::wss_onError(QAbstractSocket::SocketError error) {
	qDebug() << "Error: " << error;
	wss_socket.abort();
	emit signal_disable_controls(false);
}

void auth::slot_start_game(QString gamekey) {
	QStringList arguments;
	arguments << "-osk_server" << const_game_ip << "-osk_token" << gamekey << "-osk_store" << "https://windsofarithia.com/store";
	auto digest = diagnostics::check_digest();
	if(digest != file_security_digest) {
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_send_tray_message("Digest check failed, please contact support.");
		emit signal_disable_controls(false);
		return;
	}

	game_process->start("core/game.exe", arguments);
	gamekey.clear();
}

void auth::slot_collect_digest_post_game() {
	if(diagnostics::check_digest() != file_security_digest) {
		if(game_process->state() != QProcess::NotRunning) {
			game_process->close();
		}
		if(wss_socket.state() == QAbstractSocket::ConnectedState || wss_socket.state() == QAbstractSocket::ConnectingState) {
			wss_socket.abort();
		}
		emit signal_send_tray_message("Digest check failed, please contact support.");
		emit signal_disable_controls(false);
	}
}

std::string auth::xor_encrypt(std::string toEncrypt) {
	auto key = 'W'; //Any char will work
	auto output = toEncrypt;

	for(uint i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;

	return output;
}
