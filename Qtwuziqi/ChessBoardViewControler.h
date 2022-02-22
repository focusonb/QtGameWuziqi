#pragma once
//#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

class ModelChess;
class GameWidget;

class BoardViewControler
{
public:
	virtual void build(QGraphicsView*graphicsView, GameWidget* widget) = 0;
	virtual void drawOneChess(QPointF& point_chess, GameWidget* widget) = 0;
	virtual QGraphicsScene* getScene() = 0;
	virtual ModelChess* getModelChess() = 0;
	virtual qreal* getChessWidth() = 0;
	//virtual void drawAChess() = 0;
protected:
	QGraphicsScene* scene;
	ModelChess* modelChess;
};
class ChessBoardViewControler :
	public BoardViewControler
{
public:
	ChessBoardViewControler(int numberOfLines = 15);

	void build(QGraphicsView*graphicsView, GameWidget* widget = nullptr) override; //draw the whole board
	void drawOneChess(QPointF& point_chess, GameWidget* widget = nullptr) override;
	QGraphicsScene* getScene() override;
	ModelChess* getModelChess() override;
	qreal* getChessWidth() override;

private:

	//property
	int numberOfLines;
	qreal width_chess;
	qreal height_chess;
	QPointF point_chess;

	//bool myturn = true; // decides white or black, black first
	//bool gamegoingon;
	//bool mypart=false;
	//bool is_matched=false;
	qreal chess_width;
};

