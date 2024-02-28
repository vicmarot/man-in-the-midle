#include <iostream>

#include "PacketCapture.h"
#include "NetworkInterfaceManager.h"

int main() {
    NetworkInterfaceManager manager;
    PacketCapture pcap;
    
    auto interfaces = manager.getAvailableInterfaces();
    if (interfaces.empty()) {
        std::cerr << "No network interfaces found." << std::endl;
        return EXIT_FAILURE;
    }

    manager.printInterfaces(interfaces);
    int selectedIndex = manager.selectInterface(interfaces);
    if (selectedIndex < 0) {
        return EXIT_FAILURE;
    }

    std::cout << "You selected: " << interfaces[selectedIndex].name << std::endl;

    pcap.startCapture(interfaces[selectedIndex].name);


    return EXIT_SUCCESS;
}
