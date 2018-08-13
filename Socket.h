#pragma once
#ifndef SOCKETC
#define SOCKETC

class Socket {
public:
	bool ConnectToHost(int PortNo, const char* IPAddress);
	void CloseConnection();
	bool sendData(const char* data);
	char* recvData();
	bool connected = false;
private:
	SOCKET s = SOCKET();
};

#endif // !SOCKETC
