//A simple game writen by the author, fyf ,and will be updated in the future just for fun and learning code.

//To build this game is easy,use vs2017 and vs qt tool on windows with MSVC,and follow  steps below:
//Step 1: Copy all these files to a new empty Qt GUI project folder .
//Step 2: Modify the uic output directory to "$(ProjectDir)"
//Step 3:Buile and run.

#include "QtGame.h"
#include <QtWidgets/QApplication>
#include <process.h>
#include <Windows.h>
#include <QMessageBox>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HANDLE semaone = CreateSemaphore(NULL, 0, 1, NULL);
	HANDLE sematwo = CreateSemaphore(NULL, 0, 1, NULL);
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
	//data.ptrgamewidget = w.getgamewidget();
	QMessageBox message(QMessageBox::Warning, "Information", "GAME OVER", QMessageBox::Yes, NULL);
	data.messagebox = &message;
	w.show();
	HANDLE handle_iswin = (HANDLE)_beginthreadex(NULL, 0, iswin_func, (void*)&data, 0, NULL);
	
	return a.exec();
}
