#pragma once
#include <qmainwindow.h>
#include "ui_game_graphics_view.h"
#include <QtCore>
#include <QtGui>
#include <map>
#include "myfunction.h"
#include "IswinThread.h"
//#include "SocketThread.h"
class SocketThread;
using namespace std;
class GameWidget :
	public QMainWindow
{
	Q_OBJECT
		
public:
	GameWidget(QMainWindow*parent=NULL);
	GameWidget(QSemaphore& semaone, QSemaphore& sematwo, QSemaphore& semathree);
	~GameWidget();
signals:
	void gameover();
	void  getaplayer();
public slots:
	void gameclose();
	Threadarg_iswin* getdata();
	void gameover_message();
	void match_message();
	void draw();
	/*void draw(bool&myturn, QPointF& point_chess, QGraphicsScene*scene, qreal& chess_width, map<QPointF, int, cmp>*&ptrchesses,
		bool& gamegoingon, QSemaphore* sematwo, QSemaphore* semaone);
	*/
	void matchplayer();
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
	QSemaphore* sematwo;
	QSemaphore* semaone;
	QSemaphore* semathree;
	IswinThread* iswinThread;
	SocketThread* socketThread;
	GameWidget* ptrgamewidget;
	bool mypart=false;
	bool is_matched=false;
};


