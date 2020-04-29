

#include "myfunction.h"
#include <QMessageBox>
//#include <QGraphicsScene>
//#include "GameWidget.h"
extern class GameWidget;

void makeBoard(QGraphicsView* graphicsView, QGraphicsScene*scene, qreal& witdth_chess, qreal& height_chess ,map<QPointF, int, cmp>*&ptrchesses)
{
	QBrush greenBrush(Qt::green);
	QPen  blackPen(Qt::black);

	qreal width_view = graphicsView->width();
	qreal height_view = graphicsView->height();
	witdth_chess = width_view / 15;
	height_chess = width_view / 15;
	int i = 0;
	for (; i < 14; ++i)
	{
		int j = 0;
		for (; j <14; ++j)
		{
			qreal x = i * witdth_chess - witdth_chess * 7;
			qreal y = j * height_chess - height_chess * 7;
			ptrchesses->insert(pair<QPointF, int>(QPointF(x, y), 0));
			scene->addRect(
				x
				, y
				, witdth_chess
				, height_chess
				, blackPen
				, greenBrush);
		}
		qreal x = i * witdth_chess - witdth_chess * 7;
		qreal y = j * height_chess - height_chess * 7;
		ptrchesses->insert(pair<QPointF, int>(QPointF(x, y), 0));
	}
	int j = 0;
	for (; j < 14; ++j)
	{
		qreal x = i * witdth_chess - witdth_chess * 7;
		qreal y = j * height_chess - height_chess * 7;
		ptrchesses->insert(pair<QPointF, int>(QPointF(x, y), 0));
	}
	qreal x = i * witdth_chess - witdth_chess * 7;
	qreal y = j * height_chess - height_chess * 7;
	ptrchesses->insert(pair<QPointF, int>(QPointF(x, y), 0));

}

QRectF  qpointtoqrectf(QPointF& point_chess,qreal& chess_width)
{
	QPointF topLeft(point_chess.rx() - chess_width * 0.4, point_chess.ry() -chess_width * 0.4);
	QPointF bottomRight(point_chess.rx() +chess_width * 0.4, point_chess.ry() +chess_width * 0.4);
	return QRectF(topLeft, bottomRight);
}
void drawachess(bool&myturn,QPointF& point_chess, QGraphicsScene*scene, qreal& chess_width,map<QPointF, int,
	cmp>*&ptrchesses, bool& gamegoingon, HANDLE* sematwo, HANDLE* semaone)
{
	pointstd(point_chess, chess_width);
	if (is_outrange(point_chess, chess_width))
	{
		return;
	}
	if (is_chessmade(ptrchesses, point_chess))
	{
		return;
	}
	QRectF rect = qpointtoqrectf(point_chess, chess_width);
	if(myturn==true)
	{
		QPen pen(Qt::black);
		QBrush brush(Qt::black);
		scene->addEllipse(rect, pen, brush);
		ptrchesses->at(point_chess) = 1;
		//if (is_win(point_chess, ptrchesses, chess_width, myturn,gamegoingon))
		//{
		//	QMessageBox message(QMessageBox::Warning, "Information", "YOU WIN!", QMessageBox::Yes, NULL);
		//	message.exec();
		//}
		ReleaseSemaphore(*sematwo, 1, NULL);
		
		//scene->addEllipse(QRectF(QPointF(-18.75, -18.75), QPointF(18.75, 18.75)), pen, brush);
		//scene->addEllipse(QRectF(QPointF(-chess_width /2, chess_width / 2), QPointF(chess_width / 2, -chess_width / 2)), pen, brush);
	}
	else
	{
		QPen pen(Qt::white);
		QBrush brush(Qt::white);
		scene->addEllipse(rect, pen, brush);
		ptrchesses->at(point_chess) = 2;
		//if (is_win(point_chess, ptrchesses, chess_width, myturn,gamegoingon))
		//{
		//	QMessageBox message(QMessageBox::Warning, "Information", "YOU WIN!", QMessageBox::Yes, NULL);
		//	message.exec();
		//}
		ReleaseSemaphore(*sematwo, 1, NULL);
		//yturn = true;

	}
	WaitForSingleObject(*semaone, INFINITE);
	if (gamegoingon == false)
	{
		QMessageBox message(QMessageBox::Warning, "Information", "GAME OVER", QMessageBox::Yes, NULL);
		message.exec();
	}
	
	
	

}
void pointstd(QPointF& point_chess, qreal& chess_width)
{
	qreal extra_x = point_chess.x()/chess_width;
	qreal extra_y= point_chess.y()/chess_width;
	int x;
	int y;
	if(extra_x<=0)
	 x=extra_x-0.5;
	else
		x = extra_x + 0.5;
	if (extra_y <= 0)
		y = extra_y - 0.5;
	else
		y = extra_y +0.5;

	point_chess.rx() = x* chess_width;
	point_chess.ry() = y* chess_width;
}


bool is_outrange(QPointF& point_chess, qreal& chess_width)
{
	if (
		((point_chess.rx() <= chess_width * 7) &&
		(point_chess.rx() >= chess_width * (-7)))
		&&
		((point_chess.ry() <= chess_width * 7) &&
		(point_chess.ry() >= chess_width * (-7)))
		)
	{
		return false;
	}
	else
		return true;
}
bool is_chessmade(map<QPointF, int, cmp>*&ptrchesses, QPointF& point_chess)
{
	if (ptrchesses->at(point_chess) != 0)
	{
		return true;
	}
	return false;
}
bool is_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn, bool& gamegoingon)
{
	if (check_row(point_chess, ptrchesses, chess_width, myturn)||
		check_col(point_chess, ptrchesses, chess_width, myturn)||
		check_obl(point_chess, ptrchesses, chess_width, myturn)||
		check_obl_a(point_chess, ptrchesses, chess_width, myturn)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}  
bool check_row(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_row_win(point_chess, ptrchesses, chess_width, 1);
	}
	if (myturn == false)
	{
		return Is_row_win(point_chess, ptrchesses, chess_width, 2);
	}
}
bool Is_row_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i)
{
	int count = -1;
	for (
		 qreal next_left_x = point_chess.rx();
		ptrchesses->at(QPointF(next_left_x, point_chess.ry())) == i;
		)
	{
		next_left_x -= chess_width;
		++count;
		if (is_outrange(QPointF(next_left_x, point_chess.ry()), chess_width))
		{
			break;
	    }  
	}
	for (
		qreal next_right_x = point_chess.rx();
		ptrchesses->at(QPointF(next_right_x, point_chess.ry())) == i;
		)
	{
		next_right_x += chess_width;
		++count;
		if (is_outrange(QPointF(next_right_x, point_chess.ry()), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
bool check_col(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_col_win(point_chess, ptrchesses, chess_width, 1);
	}
	if (myturn == false)
	{
		return Is_col_win(point_chess, ptrchesses, chess_width, 2);
	}
}
bool Is_col_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i)
{
	int count = -1;
	for (
		qreal next_down_y= point_chess.ry();
		ptrchesses->at(QPointF( point_chess.rx(), next_down_y)) == i;	
		)
	{
		next_down_y += chess_width;
		++count;
		if (is_outrange(QPointF(point_chess.rx(), next_down_y), chess_width))
		{
			break;
		}
	}
	for (
		qreal next_up_y = point_chess.ry();
		ptrchesses->at(QPointF(point_chess.rx(), next_up_y)) == i;
		)
	{
		next_up_y -= chess_width;
		++count;
		if (is_outrange(QPointF(point_chess.rx(), next_up_y), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}

bool check_obl(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_obl_win(point_chess, ptrchesses, chess_width, 1);
	}
	if (myturn == false)
	{
		return Is_obl_win(point_chess, ptrchesses, chess_width, 2);
	}
}
bool Is_obl_win(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i)
{
	int count = -1;
	//QPointF temp = point_chess;
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->at(QPointF(p.first,p.second)) == i;
		)
	{
		p.first -= chess_width, p.second -= chess_width;
		++count;
		if (is_outrange(QPointF(p.first, p.second), chess_width))
		{
			break;
		}
			
	}
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->at(QPointF(p.first,p.second ) )== i;
		)
	{
		p.first += chess_width, p.second += chess_width;
		++count;
		if (is_outrange(QPointF(p.first, p.second), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
bool check_obl_a(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_obl_win_a(point_chess, ptrchesses, chess_width, 1);
	}
	if (myturn == false)
	{
		return Is_obl_win_a(point_chess, ptrchesses, chess_width, 2);
	}
}
bool Is_obl_win_a(QPointF& point_chess, map<QPointF, int, cmp>*&ptrchesses, qreal& chess_width, int i)
{
	int count = -1;
	//QPointF temp = point_chess;
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->at(QPointF(p.first,p.second)) == i;
		)
	{
		p.first += chess_width, p.second -= chess_width;
		++count;
		if (is_outrange(QPointF(p.first, p.second), chess_width))
		{
			break;
		}
	}
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->at(QPointF(p.first,p.second)) == i;
		)
	{
		p.first -= chess_width, p.second += chess_width;
		++count;
		if (is_outrange(QPointF(p.first, p.second), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
unsigned WINAPI iswin_func(void*arg)
{
	//GameWidget* p = ((*((Threadarg_iswin*)arg)).ptrgamewidget);
	while (1)
	{
		WaitForSingleObject(*((*((Threadarg_iswin*)arg)).sematwo), INFINITE);
		if (
			is_win(*((*((Threadarg_iswin*)arg)).point_chess),
				*((*((Threadarg_iswin*)arg)).ptrchesses),
				*((*((Threadarg_iswin*)arg)).chess_width),
				*((*((Threadarg_iswin*)arg)).myturn),
				*((*((Threadarg_iswin*)arg)).gamegoingon)
			))
		{
			*((*((Threadarg_iswin*)arg)).gamegoingon) = false;
		}
		if ((*((*((Threadarg_iswin*)arg)).myturn)) == true)
		{
			(*((*((Threadarg_iswin*)arg)).myturn) )= false;
		}
		else
		{
			(*((*((Threadarg_iswin*)arg)).myturn))= true;
		}
		ReleaseSemaphore(*((*((Threadarg_iswin*)arg)).semaone), 1, NULL);
	}


	return 0;
}