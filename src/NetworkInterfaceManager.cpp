#include "NetworkInterfaceManager.h"
#include <iostream>
// Include necesarios para getifaddrs en sistemas UNIX
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

std::vector<NetworkInterface> NetworkInterfaceManager::getAvailableInterfaces() {
    std::vector<NetworkInterface> interfaces;
    struct ifaddrs *ifaddr, *ifa;
    int family;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    // Recorrer la lista de interfaces
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;  

        family = ifa->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) { // Filtrar por IPv4 y IPv6
            interfaces.emplace_back(ifa->ifa_name, "");
        }
    }

    freeifaddrs(ifaddr);
    return interfaces;
}

void NetworkInterfaceManager::printInterfaces(const std::vector<NetworkInterface>& interfaces) {
    int index = 0;
    for (const auto& interface : interfaces) {
        std::cout << index++ << ": " << interface.name << std::endl;
    }
}

int NetworkInterfaceManager::selectInterface(const std::vector<NetworkInterface>& interfaces) {
    int selectedIndex = -1;
    std::cout << "Select an interface by number: ";
    std::cin >> selectedIndex;

    if (selectedIndex < 0 || selectedIndex >= interfaces.size()) {
        std::cerr << "Invalid selection." << std::endl;
        return -1;
    }

    return selectedIndex;
}
