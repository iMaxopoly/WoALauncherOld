#include "mywoalauncher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyWoALauncher w;
	w.show();
	return a.exec();
}
