#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QObject>
#include <QCryptographicHash>
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QDir>

class diagnostics : public QObject
{
    Q_OBJECT
public:
	explicit diagnostics(QObject *parent = nullptr);
	~diagnostics() {};
	static QString check_filesystem();
	static QString check_digest();
};

#endif // DIAGNOSTICS_H