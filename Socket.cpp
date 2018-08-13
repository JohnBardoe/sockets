#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Socket.h"

bool Socket::ConnectToHost(int PortNo, const char* IPaddress) {
	WSADATA wsa;
	struct sockaddr_in server;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return 1;

	inet_pton(AF_INET, IPaddress, &(server.sin_addr));
	server.sin_family = AF_INET;
	server.sin_port = htons(PortNo);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
		return 1;
	connected = true;
	return 0;
}

void Socket::CloseConnection() {
	closesocket(s);
	WSACleanup();
	connected = false;
}

bool Socket::sendData(const char* message) {
	if (send(s, message, strlen(message), 0) < 0)
		return 1;
	return 0;
}

char* Socket::recvData() {
	char data;
	int data_read;
	char* message;
	while ((data_read = recv(s, &data, 1, 0)) > 0 && data != '\n')
		*message++ = data;
	if (data_read == -1) {
		return (char*)"";
	}
	*message = '\0';
	return message;
}

