#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <process.h>
#include <string>
#include <Ws2tcpip.h>
#include <iostream>
using namespace std;
void ErrorHandling(string&s);
void makeEvent(SOCKET&sock, WSAEVENT&event, int fd);
void looprecvsend(SOCKET&sock, WSAEVENT&event, WSANETWORKEVENTS&netevent, char*msg, int size);
void sendachesss(string& s);