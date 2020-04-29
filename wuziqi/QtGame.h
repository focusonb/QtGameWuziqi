#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGame.h"
//#include "ui_WangYiYun.h"
#include "GameWidget.h"
#include "qprocess.h"

//class GameWindow :public QMainWindow
//{
//	Q_OBJECT
//public slots:
//	void comeback()
//	{
//		this->hide();
//	}
//
//};

class QtGame : public QMainWindow
{
	Q_OBJECT

public:
	QtGame(QWidget *parent = Q_NULLPTR);
	QtGame(HANDLE& semaone,HANDLE& sematwo);
	GameWidget*& getgamewidget() { return gamewidget; }

private:
	Ui::QtGameClass ui;
	//Ui::MainWindow*u;          //builder of another window
	//GameWindow *gamewindow;    // parent of another window
	GameWidget* gamewidget;
	
public slots:
		void do_it_pressed()
		{
		//	gamewindow->show();
		//	gamewindow->activateWindow();
		//	gamewindow->raise();
			gamewidget->show();
			gamewidget->activateWindow();
			gamewidget->raise();
		}

		void closegame();
};
