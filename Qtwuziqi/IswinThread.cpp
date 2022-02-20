#include "IswinThread.h"
IswinThread::IswinThread(Threadarg_iswin*a)
{
	arg = a;
}
void IswinThread:: run(void)
{
	while (1)
	{
		(*((*((Threadarg_iswin*)arg)).sematwo)).acquire();
		if (
			is_win(*((*((Threadarg_iswin*)arg)).point_chess),
				*((*((Threadarg_iswin*)arg)).ptrchesses),
				*((*((Threadarg_iswin*)arg)).chess_width),
				*((*((Threadarg_iswin*)arg)).myturn),
				*((*((Threadarg_iswin*)arg)).gamegoingon)
			))
		{
			*((*((Threadarg_iswin*)arg)).gamegoingon) = false;
			//emit (*((*((Threadarg_iswin*)arg)).ptrgamewidget))->gameover();
			emit gameover();
		}
		if ((*((*((Threadarg_iswin*)arg)).myturn)) == true)
		{
			(*((*((Threadarg_iswin*)arg)).myturn)) = false;
		}
		else
		{
			(*((*((Threadarg_iswin*)arg)).myturn)) = true;
		}
		(*((*((Threadarg_iswin*)arg)).semaone)).release();
	}
}