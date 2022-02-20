
#include "QtGame.h"
#include <QtWidgets/QApplication>
#include <process.h>
#include <Windows.h>
#include <QMessageBox>
#include "IswinThread.h"
#include <qsemaphore.h>
//struct Threadarg_iswin;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSemaphore semaone(1) ;
	QSemaphore sematwo ;
	QSemaphore semathree;
	QtGame w(semaone,sematwo, semathree);
	w.show();
	return a.exec();
}
