#pragma once
#include "myfunction.h"

using namespace std;


using MapPoint = map<QPointF, int, cmp>;
class ModelChess
{
public:
	virtual void construct() = 0;
	virtual void insertOneData(qreal x, qreal y) = 0;
	virtual MapPoint* getModelMapChess() = 0;
	virtual MapPoint** getMapPointAdr() = 0;

};
class ModelMapChess :
	public ModelChess
{
public:
	ModelMapChess();
	void construct() override;
	void insertOneData(qreal x, qreal y) override;
	MapPoint* getModelMapChess() override;
	MapPoint** getMapPointAdr() override;
private:
	MapPoint* modelMapChess;
};

