#ifndef SOCKET_H
#define SOCKET_H
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include<QMessageBox>

#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512

class Socket
{
public:
    Socket(PCSTR host = "localhost", PCSTR port = "9000");
    void connectTo();
    void sendMessage(QString text);
    void disconnect();
private:
    PCSTR host;
    PCSTR port;
    WSADATA wsaData;
    SOCKET connectSocket;
    struct addrinfo* result;
    struct addrinfo hints;
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];

};

#endif // SOCKET_H
