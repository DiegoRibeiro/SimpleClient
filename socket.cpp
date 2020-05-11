#include "socket.h"

Socket::Socket(PCSTR host, PCSTR port)
{
    this->host = host;
    this->port = port;
    this->connectSocket = INVALID_SOCKET;
}

void Socket::connectTo() {
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (iResult != 0) {
        QMessageBox box;
        box.setText("WSAStartup failed with error: " + QString::number(iResult));
        box.exec();
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    QMessageBox box;
    QString strHost(this->host);
    QString strPort(this->port);
    box.setText("Trying to connect to " + strHost + " " + strPort);
    box.exec();

    iResult = getaddrinfo(this->host, this->port, &hints, &result);
    if (iResult != 0) {
        WSACleanup();
        QMessageBox box;
        box.setText("getaddrinfo failed with error: " + QString::number(iResult));
        box.exec();
        return;
    }

    struct addrinfo* ptr;

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        // Create a SOCKET for connecting to server
        connectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (connectSocket == INVALID_SOCKET) {
            WSACleanup();
            QMessageBox box;
            box.setText("socket failed with error: " + QString::number(WSAGetLastError()));
            box.exec();
            return;
        }

        // Connect to server.
        iResult = connect(connectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(connectSocket);
            connectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (connectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        QMessageBox box;
        box.setText("Unable to connect to server!");
        box.exec();
        return;
    }
}

void Socket::sendMessage(QString text) {
    // Send an initial buffer
    int iResult = send(connectSocket, text.toStdString().c_str(), text.length(), 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        WSACleanup();
        QMessageBox box;
        box.setText("send failed with error: " + QString::number(WSAGetLastError()));
        box.exec();
        return;
    }

    iResult = recv(connectSocket, recvbuf, DEFAULT_BUFLEN, 0);
    if (iResult > 0) {
        printf("Bytes received: %d\n", iResult);
        printf("echoed: %.*s\n", iResult, recvbuf);
    }
    else if (iResult == 0) {
        this->disconnect();
    }
    else {
        QMessageBox box;
        box.setText("recv failed with error: " + QString::number(WSAGetLastError()));
        box.exec();
    }
}

void Socket::disconnect() {
    // shutdown the connection since no more data will be sent
    int iResult = shutdown(connectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(connectSocket);
        WSACleanup();
        QMessageBox box;
        box.setText("shutdown failed with error: " + QString::number(WSAGetLastError()));
        box.exec();
        return;
    }

    // cleanup
    closesocket(connectSocket);
    WSACleanup();
    QMessageBox box;
    box.setText("Disconnected from the server.");
    box.exec();
}

