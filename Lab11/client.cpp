#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Սերվերի IP հասցեն
    serverAddr.sin_port = htons(8888);

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    std::cout << "Connected to server!" << std::endl;

    char buffer[1024];
    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(buffer, sizeof(buffer));

        send(clientSocket, buffer, strlen(buffer), 0);

        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';
        std::cout << "Server replied: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
