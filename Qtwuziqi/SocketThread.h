#pragma once

//#define _WINSOCK_DEPRECATED_NO_WARNINGS 
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <WinSock2.h>
//#include <process.h>
//#include <string>
//#include <Ws2tcpip.h>
//#include <iostream>
#include "mysocketfunc.h"
#include <qthread.h>
#include "myfunction.h"



class SocketThread :
	public QThread
{
	Q_OBJECT;
private:
	WSADATA wsaData;
	SOCKET hServSock, loopsock;
	SOCKADDR_IN servAdr, loopAdr;
	WSAEVENT newEvent;
	WSANETWORKEVENTS netevent;
	char msg[100];
	Threadarg_iswin* arg;
	bool stopwait = true;
	//WSANETWORKEVENTS event;
signals:
	//void received(bool&myturn, QPointF& point_chess, QGraphicsScene*scene, qreal& chess_width, map<QPointF, int, cmp>*&ptrchesses,
	//	bool& gamegoingon, QSemaphore* sematwo, QSemaphore* semaone);
	void received();
	void successmatch();
public:
	SocketThread(Threadarg_iswin* a = NULL);
	void run(void)override;
	void sendachesss(string& s, SOCKET&sock);
	void looprecvsend(SOCKET&sock, WSAEVENT&event, WSANETWORKEVENTS&netevent, char*msg, int size, Threadarg_iswin* arg);
	SOCKET& getsocket();
public slots:
	void gamestart();

};


