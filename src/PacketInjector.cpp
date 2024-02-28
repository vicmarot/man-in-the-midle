#include "PacketCapture.h"
#include <iostream>

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    std::cout << "Packet captured with size " << pkthdr->len << " bytes" << std::endl;
}

void PacketCapture::startCapture(const std::string& interface) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (descr == nullptr) {
        std::cerr << "pcap_open_live() fails: " << errbuf << std::endl;
        return;
    }
    pcap_loop(descr, 0, packetHandler, nullptr);
}
