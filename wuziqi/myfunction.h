#pragma once
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <map>
//#include "GameWidget.h"
//#include "struct_iswin.h"
//#include <utility>
using namespace std;
extern class GameWidget;
extern class QMessageBox;
struct cmp
{
public:
	bool operator()(const QPointF& a, const QPointF& b)const
	{
		{
			if (a.y() < b.y())
			{
				return true;
			}
			else if (a.y() >b.y())
			{
				return false;
			}
			else if (a.y() == b.y())
			{
				if (a.x() == b.x())
				{
					return false;
				}
				else if (a.x() < b.x())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}


};
struct Threadarg_iswin
{
	QPointF* point_chess;
	map<QPointF, int, cmp>** ptrchesses;
	qreal* chess_width;
	bool* myturn;
	bool* gamegoingon;
	HANDLE* semaone;
	HANDLE* sematwo;
	//GameWidget* ptrgamewidget;
	QMessageBox* messagebox;
};
void makeBoard(QGraphicsView* graphicsView, QGraphicsScene*scene, qreal& witdth_chess, qreal& height_chess, map<QPointF, int, cmp>*&ptrchesses);
void drawachess(bool&myturn, QPointF& point_chess, QGraphicsScene*scene, qreal& chess_width, map<QPointF, int, cmp>*&ptrchesses,
	bool& gamegoingon, HANDLE* sematwo,HANDLE* semaone);
QRectF  qpointtoqrectf(QPointF& point_chess, qreal& chess_width);
void pointstd(QPointF& point_chess,qreal& chess_width);
bool is_outrange(QPointF& point_chess, qreal& chess_width);
bool is_chessmade(map<QPointF, int, cmp>*&ptrchesses, QPointF& point_chess);
bool is_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn, bool& gamegoingon);
bool check_row(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn);
bool Is_row_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i);
bool check_col(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn);
bool Is_col_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i);
bool check_obl(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn);
bool Is_obl_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i);
bool check_obl_a(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn);
bool Is_obl_win_a(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i);
unsigned WINAPI iswin_func(void*arg);