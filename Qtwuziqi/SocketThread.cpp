
#include "SocketThread.h"
#include <qmessagebox.h>
//#include "mysocketfunc.h"

void SocketThread::run(void)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		string tmp("WSAStartup() error!");
		ErrorHandling(tmp);
	}
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	//servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_addr.s_addr = htonl(0x7f000001);
	//servAdr.sin_addr.s_addr = htonl(0x84a10068);
	servAdr.sin_port = htons(atoi("9198"));
	(*((*((Threadarg_iswin*)arg)).semathree)).acquire();
	if (::connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) != SOCKET_ERROR)
	{
		//string tmp("connect error!");
		//cout << "connect succeed!" << endl;
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		*((*((Threadarg_iswin*)arg)).mypart) = true;
		*((*((Threadarg_iswin*)arg)).is_matched) = true;
		emit successmatch();
		looprecvsend(hServSock, newEvent, netevent, msg, sizeof(msg),arg);
	}
	else
	{
		loopsock = socket(PF_INET, SOCK_STREAM, 0);
		memset(&loopAdr, 0, sizeof(loopAdr));
		loopAdr.sin_family = AF_INET;
		loopAdr.sin_addr.s_addr = htonl(INADDR_ANY);
		loopAdr.sin_port = htons(atoi("9198"));
		if (::bind(loopsock, (SOCKADDR*)&loopAdr, sizeof(loopAdr)) == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "bind error", QMessageBox::Yes, NULL);
			message.exec();
			return;
		}

		if (::listen(loopsock, 5) == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "listen error", QMessageBox::Yes, NULL);
			message.exec();
		}
		SOCKADDR_IN clntAdr;
		int clntAdrLen = sizeof(clntAdr);
		hServSock = ::accept(loopsock, (SOCKADDR*)&clntAdr, &clntAdrLen);
		if (hServSock == SOCKET_ERROR)
		{
			QMessageBox message(QMessageBox::Warning, "Information", "accept error", QMessageBox::Yes, NULL);
			message.exec();
		}
		newEvent = WSACreateEvent();
		makeEvent(hServSock, newEvent, FD_READ);
		*((*((Threadarg_iswin*)arg)).is_matched) = true;
		looprecvsend(hServSock, newEvent, netevent, msg, sizeof(msg), arg);

	}


	return;
}
void SocketThread::sendachesss(string& s,SOCKET&sock)
{
	memset(msg, 0, s.size());
	s.copy(msg, s.size(), 0);
	send(sock, msg, sizeof(msg), 0);
	memset(msg, 0, s.size());
}
void SocketThread::looprecvsend(SOCKET&sock, WSAEVENT&event, WSANETWORKEVENTS&netevent, char*msg, int size, Threadarg_iswin* arg)
{
	while (1)
	{
		WSAWaitForMultipleEvents(1, &event, false, WSA_INFINITE, FALSE);
		WSAEnumNetworkEvents(sock, event, &netevent);
		if (netevent.iErrorCode[FD_READ_BIT] != 0)
		{
			cout << "read error" << endl;
			break;
		}
		int strlen = recv(sock, msg, size, 0);
		string recstr(msg);
		split_a(recstr, *((*((Threadarg_iswin*)arg)).point_chess));
		emit received();
		//cout << msg << endl;
		//send(sock, msg, size, 0);
	}
}
SOCKET& SocketThread::getsocket()
{
	return hServSock;
}
void SocketThread::gamestart()
{
	//this->exit();
	////WSACloseEvent(newEvent);
	////closesocket(hServSock);
	//hServSock = socket(PF_INET, SOCK_STREAM, 0);
	//memset(&servAdr, 0, sizeof(servAdr));
	//servAdr.sin_family = AF_INET; 
	////servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	//servAdr.sin_addr.s_addr = htonl(0x7f000001);
	////servAdr.sin_addr.s_addr = htonl(0x84a10068);
	//servAdr.sin_port = htons(atoi("9198"));
	//if (::connect(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) != SOCKET_ERROR)
	//{
	//	*((*((Threadarg_iswin*)arg)).mypart) = true;
	//	*((*((Threadarg_iswin*)arg)).is_matched) = true;
	//	QMessageBox message(QMessageBox::Warning, "Information", "matched one player successfully", QMessageBox::Yes, NULL);
	//	message.exec();

	//}
	(*((*((Threadarg_iswin*)arg)).semathree)).release();
}
SocketThread::SocketThread(Threadarg_iswin* a)
{
	arg = a;
}