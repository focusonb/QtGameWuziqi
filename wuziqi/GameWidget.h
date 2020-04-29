#pragma once
#include <qmainwindow.h>
#include "ui_game_graphics_view.h"
#include <QtCore>
#include <QtGui>
#include <map>
#include "myfunction.h"

using namespace std;
class GameWidget :
	public QMainWindow
{
	Q_OBJECT
		
public:
	GameWidget(QMainWindow*parent=NULL);
	GameWidget(HANDLE& semaone, HANDLE& sematwo);
signals:
	void gameover();
public slots:
	void gameclose();
	Threadarg_iswin* getdata();
	void gameover_message();
	
protected:
	void mousePressEvent(QMouseEvent*e)override;

private:
	
	Ui::MainWindow ui;
	QGraphicsScene* scene;
	QGraphicsRectItem* rect;
	bool myturn = true;
	qreal width_chess;
	qreal height_chess;
	map<QPointF, int, cmp>* chesses;
	bool gamegoingon = true;
	Threadarg_iswin arg_iswin;
	QPointF achess;
	HANDLE* sematwo;
	HANDLE* semaone;
};


