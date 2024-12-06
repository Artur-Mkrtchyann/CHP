#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

std::vector<std::string> getIPAddresses() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return {"Failed to get hostname"};
    }

    struct addrinfo hints, *res = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        return {"Failed to get address info"};
    }

    std::vector<std::string> ipAddresses;
    char ipStr[INET6_ADDRSTRLEN];

    for (struct addrinfo* p = res; p != nullptr; p = p->ai_next) {
        void* addr;
        std::string ipVersion;

        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipVersion = "IPv4: ";
        } else if (p->ai_family == AF_INET6) { // IPv6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipVersion = "IPv6: ";
        } else {
            continue; // Skip other protocols
        }

        inet_ntop(p->ai_family, addr, ipStr, sizeof(ipStr));
        ipAddresses.push_back(ipVersion + std::string(ipStr));
    }

    freeaddrinfo(res);
    return ipAddresses;
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
#endif

    auto ips = getIPAddresses();
    std::cout << "IP Addresses of the device:" << std::endl;
    for (const auto& ip : ips) {
        std::cout << ip << std::endl;
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
