#include "ModelMapChess.h"

ModelMapChess::ModelMapChess():modelMapChess(new MapPoint())
{

}
void ModelMapChess::construct()
{

}
void ModelMapChess::insertOneData(qreal x, qreal y)
{
	modelMapChess->insert(pair<QPointF, int>(QPointF(x, y), 0));
}

MapPoint * ModelMapChess::getModelMapChess()
{
	return modelMapChess;
}

MapPoint ** ModelMapChess::getMapPointAdr()
{
	return &modelMapChess;
}
