#pragma once
#include <qthread.h>
#include "myfunction.h"
class IswinThread :
	public QThread
{
	Q_OBJECT;
private:
	Threadarg_iswin* arg;
signals:
	void gameover();
public:
	IswinThread(Threadarg_iswin*a=NULL);
	void run(void)override;


};

