
#pragma once

#include <libnet.h>
#include <string>

class PacketInjector {
public:
    PacketInjector(const std::string& interface);
    ~PacketInjector();

    // Inicializa libnet
    bool init();

    // Envía un paquete
    bool sendPacket(const uint8_t* payload, size_t payloadSize, const std::string& dstIp, const std::string& srcIp);

private:
    std::string interface;
    libnet_t* l;
    char errbuf[LIBNET_ERRBUF_SIZE];
};
