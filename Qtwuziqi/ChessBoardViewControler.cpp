
#include "ChessBoardViewControler.h"
#include "GameWidget.h"
#include "ModelMapChess.h"

ChessBoardViewControler::ChessBoardViewControler(int numberOfLines)
										:numberOfLines(numberOfLines)																	
{
}
void ChessBoardViewControler::build(QGraphicsView*graphicsView, GameWidget* widget)
{
	modelChess = new ModelMapChess();
	scene = new QGraphicsScene(widget),
	graphicsView->setScene(scene);
	qreal width_view = graphicsView->width();
	qreal height_view = graphicsView->height();
	width_chess = width_view / 15;
	height_chess = width_view / 15;
	makeBoard(graphicsView, scene, width_chess, height_chess, modelChess->getModelMapChess());
}
void ChessBoardViewControler::drawOneChess(QPointF & point_chess, GameWidget* widget)
{
	drawachess(*widget->getMyturn(), point_chess, scene, width_chess, modelChess->getModelMapChess(), *widget->getGamegoingon(), widget->getQSemaphoreTwo(), widget->getQSemaphoreOne());
}
QGraphicsScene* ChessBoardViewControler::getScene()
{
	return scene;
}

ModelChess * ChessBoardViewControler::getModelChess()
{
	return modelChess;
}

qreal * ChessBoardViewControler::getChessWidth()
{
	return &chess_width;
}


