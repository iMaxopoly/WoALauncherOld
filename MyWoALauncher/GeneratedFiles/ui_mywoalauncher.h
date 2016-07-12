/********************************************************************************
** Form generated from reading UI file 'mywoalauncher.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWOALAUNCHER_H
#define UI_MYWOALAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWoALauncher
{
public:
    QWidget *centralWidget;
    QPushButton *button_facebook;
    QPushButton *button_play;
    QPushButton *button_twitter;
    QPushButton *button_close;
    QProgressBar *progress_bar;
    QLabel *label_status;
    QLabel *ProgressBarOverlay;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_username;
    QPushButton *button_youtube;
    QPushButton *button_minimize;
    QTextBrowser *textbrowser_news;

    void setupUi(QMainWindow *MyWoALauncher)
    {
        if (MyWoALauncher->objectName().isEmpty())
            MyWoALauncher->setObjectName(QStringLiteral("MyWoALauncher"));
        MyWoALauncher->resize(523, 614);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MyWoALauncher->sizePolicy().hasHeightForWidth());
        MyWoALauncher->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/favicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MyWoALauncher->setWindowIcon(icon);
        centralWidget = new QWidget(MyWoALauncher);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setStyleSheet(QLatin1String("QWidget#centralWidget{\n"
"image: url(:/Resources/base.png);\n"
"}"));
        button_facebook = new QPushButton(centralWidget);
        button_facebook->setObjectName(QStringLiteral("button_facebook"));
        button_facebook->setGeometry(QRect(90, 80, 11, 11));
        button_facebook->setFocusPolicy(Qt::NoFocus);
        button_facebook->setContextMenuPolicy(Qt::NoContextMenu);
        button_facebook->setAcceptDrops(false);
        button_facebook->setStyleSheet(QLatin1String("QPushButton#button_facebook\n"
"{\n"
"border-image: url(:/Resources/facebook.png);\n"
"}\n"
"QPushButton#button_facebook:pressed\n"
"{\n"
"border-image: url(:/Resources/facebook.png);\n"
"}\n"
""));
        button_facebook->setFlat(true);
        button_play = new QPushButton(centralWidget);
        button_play->setObjectName(QStringLiteral("button_play"));
        button_play->setGeometry(QRect(340, 230, 106, 88));
        button_play->setMaximumSize(QSize(106, 88));
        button_play->setFocusPolicy(Qt::NoFocus);
        button_play->setContextMenuPolicy(Qt::NoContextMenu);
        button_play->setStyleSheet(QLatin1String("QPushButton#button_play\n"
"{\n"
"border-image: url(:/Resources/play.png);\n"
"}\n"
"QPushButton#button_play:pressed\n"
"{\n"
"border-image: url(:/Resources/play_glow.png);\n"
"}\n"
"QPushButton#button_play:disabled\n"
"{\n"
"border-image: url(:/Resources/play_disable.png);\n"
"}\n"
""));
        button_play->setFlat(true);
        button_twitter = new QPushButton(centralWidget);
        button_twitter->setObjectName(QStringLiteral("button_twitter"));
        button_twitter->setGeometry(QRect(109, 80, 12, 11));
        button_twitter->setFocusPolicy(Qt::NoFocus);
        button_twitter->setContextMenuPolicy(Qt::NoContextMenu);
        button_twitter->setStyleSheet(QLatin1String("QPushButton#button_twitter\n"
"{\n"
"border-image: url(:/Resources/twitter.png);\n"
"}\n"
"QPushButton#button_twitter:pressed\n"
"{\n"
"border-image: url(:/Resources/twitter.png);\n"
"}\n"
""));
        button_twitter->setFlat(true);
        button_close = new QPushButton(centralWidget);
        button_close->setObjectName(QStringLiteral("button_close"));
        button_close->setGeometry(QRect(490, 50, 11, 12));
        button_close->setFocusPolicy(Qt::NoFocus);
        button_close->setContextMenuPolicy(Qt::NoContextMenu);
        button_close->setAutoFillBackground(false);
        button_close->setStyleSheet(QLatin1String("QPushButton#button_close\n"
"{\n"
"border-image: url(:/Resources/close.png);\n"
"}\n"
"QPushButton#button_close:pressed\n"
"{\n"
"border-image: url(:/Resources/close.png);\n"
"}\n"
""));
        button_close->setFlat(true);
        progress_bar = new QProgressBar(centralWidget);
        progress_bar->setObjectName(QStringLiteral("progress_bar"));
        progress_bar->setEnabled(true);
        progress_bar->setGeometry(QRect(100, 528, 178, 14));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        progress_bar->setFont(font);
        progress_bar->setStyleSheet(QLatin1String("QProgressBar#progress_bar{\n"
"border-width: 1px;\n"
"text-align: center;\n"
"color:rgba(0,0,0,100);\n"
"border-radius: 5px;\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));\n"
"}\n"
"\n"
"QProgressBar#progress_bar::chunk {\n"
"background-color: #6f9aa8;\n"
"border-radius: 5px;\n"
"}"));
        progress_bar->setValue(0);
        progress_bar->setAlignment(Qt::AlignCenter);
        progress_bar->setTextVisible(true);
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setGeometry(QRect(118, 564, 251, 20));
        label_status->setFont(font);
        label_status->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        label_status->setFrameShape(QFrame::NoFrame);
        label_status->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        ProgressBarOverlay = new QLabel(centralWidget);
        ProgressBarOverlay->setObjectName(QStringLiteral("ProgressBarOverlay"));
        ProgressBarOverlay->setEnabled(true);
        ProgressBarOverlay->setGeometry(QRect(103, 550, 281, 31));
        ProgressBarOverlay->setContextMenuPolicy(Qt::NoContextMenu);
        ProgressBarOverlay->setPixmap(QPixmap(QString::fromUtf8(":/Resources/Progress1.png")));
        lineEdit_password = new QLineEdit(centralWidget);
        lineEdit_password->setObjectName(QStringLiteral("lineEdit_password"));
        lineEdit_password->setGeometry(QRect(204, 272, 107, 19));
        lineEdit_password->setAutoFillBackground(false);
        lineEdit_password->setStyleSheet(QLatin1String("QLineEdit#lineEdit_password\n"
"{\n"
"	color: rgb(234, 234, 234);\n"
"	border-radius: 8px;\n"
"	background-color: #314567;\n"
"}"));
        lineEdit_password->setMaxLength(20);
        lineEdit_password->setFrame(false);
        lineEdit_password->setEchoMode(QLineEdit::Password);
        lineEdit_password->setAlignment(Qt::AlignCenter);
        lineEdit_username = new QLineEdit(centralWidget);
        lineEdit_username->setObjectName(QStringLiteral("lineEdit_username"));
        lineEdit_username->setGeometry(QRect(65, 272, 107, 19));
        lineEdit_username->setAutoFillBackground(false);
        lineEdit_username->setStyleSheet(QLatin1String("QLineEdit#lineEdit_username\n"
"{\n"
"	color: rgb(234, 234, 234);\n"
"	border-radius: 8px;\n"
"	background-color: #314567;\n"
"}"));
        lineEdit_username->setMaxLength(10);
        lineEdit_username->setFrame(false);
        lineEdit_username->setEchoMode(QLineEdit::Normal);
        lineEdit_username->setAlignment(Qt::AlignCenter);
        button_youtube = new QPushButton(centralWidget);
        button_youtube->setObjectName(QStringLiteral("button_youtube"));
        button_youtube->setGeometry(QRect(129, 80, 12, 11));
        button_youtube->setFocusPolicy(Qt::NoFocus);
        button_youtube->setContextMenuPolicy(Qt::NoContextMenu);
        button_youtube->setStyleSheet(QLatin1String("QPushButton#button_youtube\n"
"{\n"
"border-image: url(:/Resources/youtube.png);\n"
"}\n"
"QPushButton#button_youtube:pressed\n"
"{\n"
"border-image: url(:/Resources/youtube.png);\n"
"}\n"
""));
        button_youtube->setFlat(true);
        button_minimize = new QPushButton(centralWidget);
        button_minimize->setObjectName(QStringLiteral("button_minimize"));
        button_minimize->setGeometry(QRect(470, 54, 12, 3));
        button_minimize->setFocusPolicy(Qt::NoFocus);
        button_minimize->setContextMenuPolicy(Qt::NoContextMenu);
        button_minimize->setAutoFillBackground(false);
        button_minimize->setStyleSheet(QLatin1String("QPushButton#button_minimize\n"
"{\n"
"border-image: url(:/Resources/minimize.png);\n"
"}\n"
"QPushButton#button_minimize:pressed\n"
"{\n"
"border-image: url(:/Resources/minimize.png);\n"
"}\n"
""));
        button_minimize->setFlat(true);
        textbrowser_news = new QTextBrowser(centralWidget);
        textbrowser_news->setObjectName(QStringLiteral("textbrowser_news"));
        textbrowser_news->setGeometry(QRect(67, 313, 241, 192));
        textbrowser_news->setStyleSheet(QLatin1String("QTextBrowser#textbrowser_news\n"
"{\n"
"	color: rgb(234, 234, 234);\n"
"	border-radius: 8px;\n"
"	background-color: #314567;\n"
"}"));
        MyWoALauncher->setCentralWidget(centralWidget);
        button_play->raise();
        button_twitter->raise();
        button_close->raise();
        button_facebook->raise();
        ProgressBarOverlay->raise();
        progress_bar->raise();
        label_status->raise();
        lineEdit_password->raise();
        lineEdit_username->raise();
        button_youtube->raise();
        button_minimize->raise();
        textbrowser_news->raise();
        QWidget::setTabOrder(lineEdit_username, lineEdit_password);

        retranslateUi(MyWoALauncher);

        QMetaObject::connectSlotsByName(MyWoALauncher);
    } // setupUi

    void retranslateUi(QMainWindow *MyWoALauncher)
    {
        MyWoALauncher->setWindowTitle(QApplication::translate("MyWoALauncher", "Winds Of Arithia 2016", 0));
        button_facebook->setText(QString());
        button_play->setText(QString());
        button_twitter->setText(QString());
        button_close->setText(QString());
        progress_bar->setFormat(QApplication::translate("MyWoALauncher", "%p%", 0));
        label_status->setText(QApplication::translate("MyWoALauncher", "Winds Of Arithia 2016", 0));
        ProgressBarOverlay->setText(QString());
        lineEdit_password->setPlaceholderText(QApplication::translate("MyWoALauncher", "Password", 0));
        lineEdit_username->setPlaceholderText(QApplication::translate("MyWoALauncher", "Username", 0));
        button_youtube->setText(QString());
        button_minimize->setText(QString());
        textbrowser_news->setHtml(QApplication::translate("MyWoALauncher", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MyWoALauncher: public Ui_MyWoALauncher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWOALAUNCHER_H
