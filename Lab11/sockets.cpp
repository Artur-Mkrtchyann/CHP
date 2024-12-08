#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock գրադարանի ավելացում

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData); 

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Սերվերի սոքեթ

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8888); // Սերվերի համար (օր.՝ 8888)

    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 3);

    std::cout << "Waiting for connections..." << std::endl;

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    std::cout << "Client connected!" << std::endl;

    char buffer[1024];
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';
        std::cout << "Client says: " << buffer << std::endl;

        send(clientSocket, buffer, bytesReceived, 0); 
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
