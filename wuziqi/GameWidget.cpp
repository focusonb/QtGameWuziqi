#include "GameWidget.h"
#include "myfunction.h"
#include <qmessagebox.h>
GameWidget::GameWidget(QMainWindow*parent):chesses(new map<QPointF, int, cmp>())
{
	ui.setupUi(this);
	scene = new QGraphicsScene(this);
	ui.graphicsView->setScene(scene);
	//map<QPointF, int, cmp>* ptrchesse;
	makeBoard(ui.graphicsView,scene, width_chess, height_chess, chesses);
	connect(this, &GameWidget::gameover, this, &GameWidget::gameover_message);
}
GameWidget::GameWidget(HANDLE& s, HANDLE& sematwo) :chesses(new map<QPointF, int, cmp>()),
sematwo (&sematwo)
{
	ui.setupUi(this);
	scene = new QGraphicsScene(this);
	ui.graphicsView->setScene(scene);
	//map<QPointF, int, cmp>* ptrchesse;
	makeBoard(ui.graphicsView, scene, width_chess, height_chess, chesses);
	semaone = &s;
	connect(this, &GameWidget::gameover, this, &GameWidget::gameover_message);
}
void GameWidget::gameclose()
{
	this->hide();


}
void GameWidget::mousePressEvent(QMouseEvent*e)
{
	//if (WaitForSingleObject(*semaone, 0)== 0x00000080L)
	//{
	//	return;
	//}
	//if (gamegoingon == false)
	//{
	//	QMessageBox message(QMessageBox::Warning, "Information", "GAME OVER", QMessageBox::Yes, NULL);
 //       message.exec();
	//	return;
	//}
	QPoint mousePos = e->pos();
	QPoint pointcentre = ui.centralwidget->mapFromParent(mousePos);
	QPoint pointwidget = ui.widget->mapFromParent(pointcentre);
	QPoint pointview = ui.graphicsView->mapFromParent(pointwidget);
	achess = ui.graphicsView->mapToScene(pointview);
	//QPointF pointScene = ui.graphicsView->mapToScene(mousePos);
	drawachess(myturn, achess,scene,width_chess, chesses,gamegoingon,sematwo,semaone);
}
Threadarg_iswin* GameWidget::getdata()
{
	arg_iswin.point_chess = &achess;
	arg_iswin.ptrchesses = &chesses;
	arg_iswin.chess_width = &width_chess;
	arg_iswin.myturn = &myturn;
	arg_iswin.gamegoingon = &gamegoingon;
	return &arg_iswin;
 }
void GameWidget::gameover_message()
{
	QMessageBox message(QMessageBox::Warning, "Information", "YOU WIN!", QMessageBox::Yes, NULL);
	message.exec();
}
