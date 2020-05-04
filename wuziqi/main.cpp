
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
	//QtGame 
	QtGame w(semaone,sematwo);
	
	Threadarg_iswin data;
	Threadarg_iswin* arg = w.getgamewidget()->getdata();
	QPointF* point_chess;
	map<QPointF, int, cmp>** ptrchesses;
	data.point_chess = (*((Threadarg_iswin*)arg)).point_chess;
	data.ptrchesses = (*((Threadarg_iswin*)arg)).ptrchesses;
	data.chess_width = (*((Threadarg_iswin*)arg)).chess_width;
	data.myturn = (*((Threadarg_iswin*)arg)).myturn;
	data.gamegoingon = (*((Threadarg_iswin*)arg)).gamegoingon;
	data.ptrchesses = (*((Threadarg_iswin*)arg)).ptrchesses;
	data.semaone = &semaone;
	data.sematwo = &sematwo;
	//IswinThread iswinThread(&data);
	//data.ptrgamewidget = w.getgamewidget();
	//QMessageBox message(QMessageBox::Warning, "Information", "GAME OVER", QMessageBox::Yes, NULL);
	//data.messagebox = &message;
	//iswinThread.start();
	w.show();

	
	return a.exec();
}
