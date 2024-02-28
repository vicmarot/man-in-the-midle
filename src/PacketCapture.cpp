#include "PacketCapture.h"
#include <iostream>
#include <netinet/ip.h>
#include <netinet/ether.h> 
#include <arpa/inet.h> 
#include <cstring> 

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    const struct ether_header* ethernetHeader;
    const struct ip* ipHeader;
    char sourceIP[INET_ADDRSTRLEN];
    char destIP[INET_ADDRSTRLEN];

    ethernetHeader = (struct ether_header*)packet;

    if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
        ipHeader = (struct ip*)(packet + sizeof(struct ether_header));

        inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIP, INET_ADDRSTRLEN);


        if (strcmp(sourceIP, "192.168.2.135") == 0 || strcmp(destIP, "192.168.2.135") == 0){
            // std::cout << "Nope " << std::endl;
        }
        else{

            std::cout << "From: " << sourceIP << " To: " << destIP;
            std::cout << " Size of the packet: " << pkthdr->len << " bytes" << std::endl;
        }

        
    } else {
        std::cout << "Not an IP packet." << std::endl;
    }
}

void PacketCapture::startCapture(const std::string& interface) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* descr = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (descr == nullptr) {
        std::cerr << "pcap_open_live() falló: " << errbuf << std::endl;
        return;
    }
    pcap_loop(descr, 0, packetHandler, nullptr);
}
