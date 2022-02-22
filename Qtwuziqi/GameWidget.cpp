#include "SocketThread.h"
#include "GameWidget.h"
#include "myfunction.h"
#include <qmessagebox.h>
#include "ChessBoardViewControler.h"
#include "ModelMapChess.h"

extern void sendachesss(string& s);
GameWidget::GameWidget(QMainWindow*parent)
{
	ui.setupUi(this);
	//scene = new QGraphicsScene(this);
	//ui.graphicsView->setScene(scene);
	//map<QPointF, int, cmp>* ptrchesse;
	//makeBoard(ui.graphicsView,scene, width_chess, height_chess, chesses);
	viewControler = new ChessBoardViewControler(15);
	viewControler->build(ui.graphicsView, this);
	iswinThread = new IswinThread(getdata());
	iswinThread->start();
	connect(this, &GameWidget::gameover, this, &GameWidget::gameover_message);
}
GameWidget::GameWidget(QSemaphore& s, QSemaphore& sematwo, QSemaphore& semathree) :
	semaone(&s), sematwo (&sematwo),semathree(&semathree)
{
	ui.setupUi(this);
	//scene = new QGraphicsScene(this);
	//ui.graphicsView->setScene(scene);
	//map<QPointF, int, cmp>* ptrchesse;
	//makeBoard(ui.graphicsView, scene, width_chess, height_chess, chesses);

	viewControler = new ChessBoardViewControler(15);
	viewControler->build(ui.graphicsView, this);



	iswinThread = new IswinThread(getdata());
	iswinThread->start();
	socketThread = new SocketThread(getdata());
	socketThread->start();
	connect(iswinThread, SIGNAL(gameover()), this, SLOT(gameover_message()));
	connect(this, &GameWidget::gameover, this, &GameWidget::gameover_message);
	connect(
		socketThread,
		SIGNAL(received()),
		this,
		SLOT(draw())
	);
	connect(this, SIGNAL(getaplayer()), socketThread, SLOT(gamestart()));
	connect(socketThread, SIGNAL(successmatch()), this, SLOT(match_message()));
}
QSemaphore * GameWidget::getQSemaphoreOne()
{
	return semaone;
}
QSemaphore * GameWidget::getQSemaphoreTwo()
{
	return sematwo;
}
bool* GameWidget::getMyturn()
{
	return &myturn;
}
bool * GameWidget::getGamegoingon()
{
	return &gamegoingon;
}
void GameWidget::gameclose()
{
	this->hide();


}
void GameWidget::mousePressEvent(QMouseEvent*e)
{
	if (is_matched == false)
	{
		QMessageBox message(QMessageBox::Warning, "Information", "Waiting for your opponent", QMessageBox::Yes, NULL);
		message.exec();
		return;
	}
	if (myturn != mypart)
	{
		QMessageBox message(QMessageBox::Warning, "Information", "Its not your turn", QMessageBox::Yes, NULL);
		message.exec();
		return;
	}
	QPoint mousePos = e->pos();
	QPoint pointcentre = ui.centralwidget->mapFromParent(mousePos);
	QPoint pointwidget = ui.widget->mapFromParent(pointcentre);
	QPoint pointview = ui.graphicsView->mapFromParent(pointwidget);
	achess = ui.graphicsView->mapToScene(pointview);
	string message_toopponent(std::to_string(achess.rx()) + 'a' + std::to_string(achess.ry()));
	socketThread->sendachesss(message_toopponent,socketThread->getsocket());
	//drawachess(myturn, achess,scene,width_chess, chesses,gamegoingon,sematwo,semaone);
	viewControler->drawOneChess(achess, this);

}
Threadarg_iswin* GameWidget::getdata()
{
	arg_iswin.point_chess = &achess;
	arg_iswin.ptrchesses = viewControler->getModelChess()->getMapPointAdr();
	arg_iswin.chess_width = viewControler->getChessWidth();
	arg_iswin.myturn = &myturn;
	arg_iswin.gamegoingon = &gamegoingon;
	arg_iswin.sematwo = sematwo;
	arg_iswin.semaone = semaone;
	arg_iswin.ptrgamewidget = this;
	arg_iswin.mypart = &mypart;
	arg_iswin.is_matched = &is_matched;
	arg_iswin.semathree = semathree;
	return &arg_iswin;
 }
void GameWidget::gameover_message()
{
	QMessageBox message(QMessageBox::Warning, "Information", "YOU WIN!", QMessageBox::Yes, NULL);
	message.exec();
}
GameWidget::~GameWidget()
{
	iswinThread->terminate();
}
//void  GameWidget::draw(bool&myturn, QPointF& point_chess, QGraphicsScene*scene, qreal& chess_width, map<QPointF, int, cmp>*&ptrchesses,
//	bool& gamegoingon, QSemaphore* sematwo, QSemaphore* semaone)
//{
//	drawachess(myturn, point_chess, scene, chess_width, ptrchesses, gamegoingon, sematwo, semaone);		
//
//}
void GameWidget::draw()
{

	//drawachess(myturn, achess, scene, width_chess, chesses, gamegoingon, sematwo, semaone);
	viewControler->drawOneChess(achess, this);
	return;
}
void GameWidget::matchplayer()
{
	emit getaplayer();
}
void GameWidget::match_message()
{
	QMessageBox message(QMessageBox::Warning, "Information", "matched one player successfully", QMessageBox::Yes, NULL);
	message.exec();
}