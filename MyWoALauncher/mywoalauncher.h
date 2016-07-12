#ifndef MYWOALAUNCHER_H
#define MYWOALAUNCHER_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMouseEvent>
#include <QTimer>
#include <QtConcurrent/QtConcurrentRun>
#include <QDesktopServices>
#include <QProcess>
#include <QFutureWatcher>
#include "osdab/unzip.h"
#include "ui_mywoalauncher.h"
#include "preconf.h"
#include "fetcher.h"
#include "diagnostics.h"
#include "auth.h"

class MyWoALauncher : public QMainWindow {
	Q_OBJECT

public:
	explicit MyWoALauncher(QWidget *parent = 0);
	~MyWoALauncher() { }

protected:
	// Setup gui movement on mouse-drag
	void mouseMoveEvent(QMouseEvent* event) override {
		if(event->buttons().testFlag(Qt::LeftButton) && mMoving) {
			this->move(this->pos() + (event->pos() - mLastMousePosition));
		}
	};
	void mousePressEvent(QMouseEvent* event) override {
		if(event->button() == Qt::LeftButton) {
			mMoving = true;
			mLastMousePosition = event->pos();
		}
	};
	void mouseReleaseEvent(QMouseEvent* event) override {
		if(event->button() == Qt::LeftButton) {
			mMoving = false;
		}
	};

public slots:
	// Setup gui Button Behaviors
	void on_button_close_clicked();
	void on_button_minimize_clicked();
	static void on_button_facebook_clicked();
	static void on_button_youtube_clicked();
	static void on_button_twitter_clicked();
	void on_button_play_clicked() const;

	// Setup tray slots
	void slot_tray_show() const;
	void slot_tray_hide() const;

public slots:
	void slot_download_progress(qint64, qint64);

private slots:
	void boot_diagnostics();
	void slot_get_news();
	void slot_get_launcher_version();
	void slot_get_game_version();
	void slot_get_launcher_updates();
	void slot_get_game_updates();
	void slot_startup_transactions_finished();

	//auth slots
	void slot_disable_controls(bool);
	void slot_notify_ui_game_started();
	void slot_notify_ui_game_closed();
	void slot_send_tray_message(QString);
	void slot_send_status(QString);

signals:
	void signal_get_news();
	void signal_get_launcher_version();
	void signal_get_game_version();
	void signal_get_launcher_updates();
	void signal_get_game_updates();
	void signal_startup_transactions_finished();

private:
	void disable_controls(bool) const;
	bool extract_file(QString, QString);
	QString update_launcher();
	QString update_game();

private:
	Ui::MyWoALauncher ui;

	// Setup window movement on mouse-drag
	QPoint mLastMousePosition;
	bool mMoving;

	// Tray Variables
	QAction *action_minimize, *action_restore, *action_quit;
	QSystemTrayIcon *tray_icon;
	QMenu *menu_tray;

	// Version variables
	QString variable_launcher_version;
	QStringList variable_game_version;

	fetcher fetch_object;
	auth *auth_object;

	// Futurewatchers
	QFutureWatcher<QString> *news_futurewatcher;
	QFutureWatcher<QString> *file_security_futurewatcher;
	QFutureWatcher<QString> *launcher_version_futurewatcher;
	QFutureWatcher<QStringList> *game_version_futurewatcher;
	QFutureWatcher<QString> *update_launcher_futurewatcher;
	QFutureWatcher<QString> *update_game_futurewatcher;

};

#endif // MYWOALAUNCHER_H
