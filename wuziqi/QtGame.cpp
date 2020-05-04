#include "QtGame.h"

QtGame::QtGame(QWidget *parent)
	: QMainWindow(parent)
	,gamewidget(new GameWidget())
{
	ui.setupUi(this);
}
QtGame::QtGame(QSemaphore& semaone, QSemaphore& sematwo)
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
