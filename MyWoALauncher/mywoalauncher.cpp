#include "mywoalauncher.h"
#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
#include <psapi.h>

MyWoALauncher::MyWoALauncher(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	// Setup frameless dialogbox
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	// Setup tray actions
	action_minimize = new QAction(tr("&Hide"), this);
	connect(action_minimize, SIGNAL(triggered()), this, SLOT(hide()));
	connect(action_minimize, SIGNAL(triggered()), this, SLOT(slot_tray_show()));
	action_restore = new QAction(tr("&Show"), this);
	connect(action_restore, SIGNAL(triggered()), this, SLOT(showNormal()));
	connect(action_restore, SIGNAL(triggered()), this, SLOT(slot_tray_hide()));
	action_quit = new QAction(tr("&Quit"), this);
	connect(action_quit, SIGNAL(triggered()), qApp, SLOT(quit()));

	// Setup tray
	menu_tray = new QMenu(this);
	menu_tray->addAction(action_minimize);
	menu_tray->addAction(action_restore);
	menu_tray->addAction(action_quit);

	// Display tray
	tray_icon = new QSystemTrayIcon(this);
	tray_icon->setContextMenu(menu_tray);
	tray_icon->setIcon(QIcon(":/Resources/favicon.png"));
	tray_icon->setToolTip(tr("WoA (offline)"));
	tray_icon->show();

	// Init ui objects
	ui.progress_bar->setValue(100);
	// Setup RegExp Validator for Username and Password fieldsa 
	QValidator *validator = new QRegExpValidator(QRegExp("[a-zA-Z0-9]+"), this);
	ui.lineEdit_username->setValidator(validator);
	ui.lineEdit_username->setMaxLength(20);
	ui.lineEdit_username->setCursorPosition(0);
	ui.lineEdit_password->setValidator(validator);
	ui.lineEdit_password->setMaxLength(20);
	ui.lineEdit_password->setCursorPosition(0);

	// Signals and slots
	connect(this, SIGNAL(signal_get_news()), this, SLOT(slot_get_news()));
	connect(this, SIGNAL(signal_get_launcher_version()), this, SLOT(slot_get_launcher_version()));
	connect(this, SIGNAL(signal_get_game_version()), this, SLOT(slot_get_game_version()));
	connect(this, SIGNAL(signal_get_launcher_updates()), this, SLOT(slot_get_launcher_updates()));
	connect(this, SIGNAL(signal_get_game_updates()), this, SLOT(slot_get_game_updates()));
	connect(this, SIGNAL(signal_startup_transactions_finished()), this, SLOT(slot_startup_transactions_finished()));

	// Class signal slots
	connect(&fetch_object, SIGNAL(signal_download_progress(qint64, qint64)), this, SLOT(slot_download_progress(qint64, qint64)));

	disable_controls(true);

	// Init auth class
	auth_object = new auth(this);
	connect(auth_object, SIGNAL(signal_disable_controls(bool)), this, SLOT(slot_disable_controls(bool)));
	connect(auth_object, SIGNAL(signal_notify_ui_game_started()), this, SLOT(slot_notify_ui_game_started()));
	connect(auth_object, SIGNAL(signal_notify_ui_game_closed()), this, SLOT(slot_notify_ui_game_closed()));
	connect(auth_object, SIGNAL(signal_send_tray_message(QString)), this, SLOT(slot_send_tray_message(QString)));
	connect(auth_object, SIGNAL(signal_send_status(QString)), this, SLOT(slot_send_status(QString)));

	// Init diagnostics, news fetching, launcher updates, patch updates	
	ui.label_status->setText(tr("Running Diagnostics..."));
	QTimer::singleShot(2000, this, SLOT(boot_diagnostics()));
}

void MyWoALauncher::on_button_close_clicked() {
	auto killProcessLauncher = [](QString processname) {
		DWORD processes[1024], count;
		if(!EnumProcesses(processes, sizeof(processes), &count)) {
			return;
		}

		count /= sizeof(DWORD);
		for(unsigned int i = 0; i < count; i++) {
			WCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
			WCHAR ourprocess[MAX_PATH];
			processname.toWCharArray(ourprocess);
			if(processes[i] != 0) {
				// remember to open with PROCESS_ALL_ACCESS, otherwise you will not be able to kill it
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processes[i]);
				if(NULL != hProcess) {
					HMODULE hMod;
					DWORD cbNeeded;
					if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
						GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

						// find the process and kill it
						if(wcsncmp(szProcessName, ourprocess, 1) == 0) {
							DWORD result = WAIT_OBJECT_0;
							while(result == WAIT_OBJECT_0) {
								// use WaitForSingleObject to make sure it's dead
								result = WaitForSingleObject(hProcess, 100);
								TerminateProcess(hProcess, 0);
							}

							CloseHandle(hProcess);
						}
					}
				}
			}
		}
	};	
	auth_object->shutting_down();
	killProcessLauncher(QFileInfo(QCoreApplication::applicationFilePath()).fileName());
}

void MyWoALauncher::on_button_minimize_clicked() { this->setWindowState(Qt::WindowMinimized); }

void MyWoALauncher::on_button_facebook_clicked() { QDesktopServices::openUrl(QUrl("https://www.facebook.com/windsofarithia")); }

void MyWoALauncher::on_button_youtube_clicked() { QDesktopServices::openUrl(QUrl("https://www.youtube.com/windsofarithia")); }

void MyWoALauncher::on_button_twitter_clicked() { QDesktopServices::openUrl(QUrl("https://www.twitter.com/windsofarithia")); }

void MyWoALauncher::on_button_play_clicked() const {
	qDebug() << Q_FUNC_INFO;
	disable_controls(true);
	ui.label_status->setText("Please wait while we log you in...");
	auth_object->dial(ui.lineEdit_username->text(), ui.lineEdit_password->text());
}

void MyWoALauncher::slot_tray_show() const {
	qDebug() << Q_FUNC_INFO;
	action_restore->setEnabled(true);
	action_minimize->setDisabled(true);
}

void MyWoALauncher::slot_tray_hide() const {
	qDebug() << Q_FUNC_INFO;
	action_restore->setDisabled(true);
	action_minimize->setEnabled(true);
}

void MyWoALauncher::slot_download_progress(qint64 read, qint64 total) {
	//	qDebug() << Q_FUNC_INFO;

	ui.progress_bar->setMaximum(total);
	ui.progress_bar->setValue(read);
}

void MyWoALauncher::disable_controls(bool val) const {
	qDebug() << Q_FUNC_INFO;

	ui.lineEdit_username->setDisabled(val);
	ui.lineEdit_password->setDisabled(val);
	ui.button_play->setDisabled(val);
}

void MyWoALauncher::boot_diagnostics() {
	qDebug() << Q_FUNC_INFO;

	file_security_futurewatcher = new QFutureWatcher<QString>(this);
	connect(file_security_futurewatcher, &QFutureWatcher<QString>::finished, [&]() {
		if(file_security_futurewatcher->result() != "") {
			tray_icon->showMessage(tr("WoA::Error"), file_security_futurewatcher->result(), tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		qDebug() << "Check - File security";
		file_security_futurewatcher->deleteLater();
		emit signal_get_news();
	});

	// Init filesystem diagnostics	
	QFuture<QString> file_security_future = QtConcurrent::run(diagnostics::check_filesystem);
	file_security_futurewatcher->setFuture(file_security_future);
}

void MyWoALauncher::slot_get_news() {
	qDebug() << Q_FUNC_INFO;

	news_futurewatcher = new QFutureWatcher<QString>(this);
	connect(news_futurewatcher, &QFutureWatcher<QString>::finished, [&]() {

		if(news_futurewatcher->result() == "") {
			tray_icon->showMessage(tr("WoA::Error"), "Error fetching server news!", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		ui.textbrowser_news->setHtml(news_futurewatcher->result());
		qDebug() << "Check News";
		news_futurewatcher->deleteLater();
		emit signal_get_launcher_version();
	});
	// Time to fetch news and then display it
	ui.label_status->setText(tr("Getting server news..."));

	QFuture<QString> news_future = QtConcurrent::run(&this->fetch_object, &fetcher::fetch_news);
	news_futurewatcher->setFuture(news_future);
}

void MyWoALauncher::slot_get_launcher_version() {
	qDebug() << Q_FUNC_INFO;

	// Here we will fetch launcher version, then game version and store in global variables
	ui.label_status->setText(tr("Retrieving remote launcher version..."));

	launcher_version_futurewatcher = new QFutureWatcher<QString>(this);
	connect(launcher_version_futurewatcher, &QFutureWatcher<QString>::finished, [&]() {
		qDebug() << "Debug launcher version: " << launcher_version_futurewatcher->result();
		if(launcher_version_futurewatcher->result() == "") {
			tray_icon->showMessage(tr("WoA::Error"), "Error retrieving remote launcher version!", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		if(std::atof(launcher_version_futurewatcher->result().toLatin1()) == 0.0) {
			tray_icon->showMessage(tr("WoA::Error"), "Error retrieving remote launcher version !", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		variable_launcher_version = launcher_version_futurewatcher->result();
		qDebug() << "Check Launcher version";
		launcher_version_futurewatcher->deleteLater();
		emit signal_get_game_version();
	});
	QFuture<QString> launcher_version_future = QtConcurrent::run(&this->fetch_object, &fetcher::fetch_launcher_version);
	launcher_version_futurewatcher->setFuture(launcher_version_future);
}

void MyWoALauncher::slot_get_game_version() {
	qDebug() << Q_FUNC_INFO;

	ui.label_status->setText(tr("Retrieving remote game version..."));

	game_version_futurewatcher = new QFutureWatcher<QStringList>(this);
	connect(game_version_futurewatcher, &QFutureWatcher<QStringList>::finished, [&]() {
		if(game_version_futurewatcher->result().length() < 1) {
			tray_icon->showMessage(tr("WoA::Error"), "Error retrieving remote game version!", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		variable_game_version = game_version_futurewatcher->result();
		qDebug() << "Check Game version" << variable_game_version;
		game_version_futurewatcher->deleteLater();
		emit signal_get_launcher_updates();
	});
	QFuture<QStringList> game_version_future = QtConcurrent::run(&this->fetch_object, &fetcher::fetch_game_version);
	game_version_futurewatcher->setFuture(game_version_future);
}

void MyWoALauncher::slot_get_launcher_updates() {
	qDebug() << Q_FUNC_INFO;

	ui.label_status->setText(tr("Updating launcher if required..."));

	update_launcher_futurewatcher = new QFutureWatcher<QString>(this);
	connect(update_launcher_futurewatcher, &QFutureWatcher<QString>::finished, [&]() {
		if(update_launcher_futurewatcher->result() == "error") {
			tray_icon->showMessage(tr("WoA::Error"), "Error retrieving launcher update!", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		} else if(update_launcher_futurewatcher->result() == "launcher_doesnt_need_restart") {
			qDebug() << "Check launcher updates";
			update_launcher_futurewatcher->deleteLater();
			emit signal_get_game_updates();
		} else if(update_launcher_futurewatcher->result() == "launcher_needs_restart") {
			QProcess::startDetached("woa.exe");
			qApp->quit();
		}
	});
	QFuture<QString> update_launcher_future = QtConcurrent::run(this, &MyWoALauncher::update_launcher);
	update_launcher_futurewatcher->setFuture(update_launcher_future);
}

void MyWoALauncher::slot_get_game_updates() {
	qDebug() << Q_FUNC_INFO;

	ui.label_status->setText(tr("Updating game if required..."));

	update_game_futurewatcher = new QFutureWatcher<QString>(this);
	connect(update_game_futurewatcher, &QFutureWatcher<QString>::finished, [&]() {
		if(update_game_futurewatcher->result() == "error") {
			tray_icon->showMessage(tr("WoA::Error"), "Error retrieving game update!", tray_icon->Critical, 3000);
			ui.label_status->setText("Winds Of Arithia 2016");
			return;
		}
		qDebug() << "Check game updates";
		update_game_futurewatcher->deleteLater();
		emit slot_startup_transactions_finished();
	});
	QFuture<QString> update_game_future = QtConcurrent::run(this, &MyWoALauncher::update_game);
	update_game_futurewatcher->setFuture(update_game_future);
}

void MyWoALauncher::slot_startup_transactions_finished() {
	qDebug() << Q_FUNC_INFO;
	tray_icon->showMessage(tr("WoA::Success"), "Game successfully updated!", tray_icon->Information, 3000);
	ui.label_status->setText(tr("Winds of Arithia 2016"));
	disable_controls(false);
}

/* Auth class relevant slots */

void MyWoALauncher::slot_disable_controls(bool val) {
	disable_controls(val);
}

void MyWoALauncher::slot_notify_ui_game_started() {
	qDebug() << Q_FUNC_INFO;
	this->hide();
}

void MyWoALauncher::slot_notify_ui_game_closed() {
	qDebug() << Q_FUNC_INFO;
	ui.label_status->setText(tr("Winds of Arithia 2016"));
	slot_disable_controls(false);
	this->showNormal();
}

void MyWoALauncher::slot_send_tray_message(QString msg) {
	qDebug() << Q_FUNC_INFO;
	tray_icon->showMessage(tr("WoA::Error"), msg, tray_icon->Warning, 3000);
	ui.label_status->setText("Winds Of Arithia 2016");
}

void MyWoALauncher::slot_send_status(QString msg) {
	qDebug() << Q_FUNC_INFO;
	ui.label_status->setText(msg);
}

bool MyWoALauncher::extract_file(QString filename, QString type) {
	qDebug() << Q_FUNC_INFO;
	UnZip uz;
	if(uz.openArchive(filename) != UnZip::Ok) {
		qDebug() << "Error Unzipping: ";
		return false;
	}
	qDebug() << "Debug extraction error checking done";
	uz.setPassword("br1nj4lp0t4t0");

	if(type == "launcher") {
		uz.extractAll("");
		uz.closeArchive();
	} else if(type == "game") {
		uz.extractAll("core");
		uz.closeArchive();
		QFile::remove(filename);
	}
	qDebug() << "Debug extraction done";
	return true;
}

QString MyWoALauncher::update_launcher() {

	if(const_launcher_version < variable_launcher_version.toDouble()) {
		auto result = fetch_object.fetch_launcher(const_launcher_download_url + "/" + variable_launcher_version);
		if(result == "") {
			return QString("error");
		}

		QFile launcher_zip;
		launcher_zip.setFileName(QString("launcher%1.zip").arg(variable_launcher_version));
		if(!launcher_zip.open(QIODevice::WriteOnly))
			return QString("error");
		launcher_zip.write(result);
		launcher_zip.close();

		if(!extract_file(QString("launcher%1.zip").arg(variable_launcher_version), "launcher")) {
			return QString("error");
		}
		return QString("launcher_needs_restart");
	}
	return QString("launcher_doesnt_need_restart");
}

QString MyWoALauncher::update_game() {
	// Now doing the bulk game patching work
	QFile local_version_file("game.version");
	if(!local_version_file.open(QIODevice::ReadOnly)) {
		return QString("error");
	}
	QTextStream inc(&local_version_file);
	auto local_version = QString(inc.readLine()).toDouble();
	local_version_file.close();

	for(auto remote_version : variable_game_version) {
		qDebug() << "Debug game version updating: " << remote_version;
		if(local_version < remote_version.toDouble()) {
			auto file_name = QString("game%1.zip").arg(remote_version);
			QByteArray result = fetch_object.fetch_game(const_gamepatch_download_url + "/" + remote_version);
			if(result == "") {
				return QString("error");
			}

			qDebug() << "Debug starting extraction process on" << file_name;
			QFile game_zip;
			game_zip.setFileName(file_name);
			if(!game_zip.open(QIODevice::WriteOnly)) {
				return QString("error");
			}
			game_zip.write(result);
			game_zip.close();

			if(!extract_file(file_name, "game")) {
				return QString("error");
			}

			// Write new game-patch number
			qDebug() << "Debug Writing patch number to disk";
			QFile file("game.version");
			if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return QString("error");
			QTextStream out2(&file);
			out2 << remote_version;
			file.close();
		}
	}
	qDebug() << "Debug Game update finished";
	return QString("success");
}
