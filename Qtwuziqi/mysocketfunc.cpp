#pragma comment(lib, "Ws2_32.lib")
#include "mysocketfunc.h"
void ErrorHandling(string&s)
{
	fputs(s.c_str(), stderr);
	fputc('\n', stderr);
	exit(1);
}
void makeEvent(SOCKET&sock, WSAEVENT&event, int fd)
{
	if (WSAEventSelect(sock, event, fd) == SOCKET_ERROR)
	{
		string tmp("WSAEventSelect error");
		ErrorHandling(tmp);
	}
}
