#include "QtGame.h"

QtGame::QtGame(QWidget *parent)
	: QMainWindow(parent)
	,gamewidget(new GameWidget())
{
	ui.setupUi(this);
}
QtGame::QtGame(HANDLE& semaone, HANDLE& sematwo)
	: QMainWindow()
	, gamewidget(new GameWidget(semaone,sematwo))
{
	ui.setupUi(this);
}
void QtGame::closegame()
{
	close();
	this->gamewidget->close();
}
