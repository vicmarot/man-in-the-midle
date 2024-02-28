// PacketCapture.h
#pragma once
#include <pcap.h>
#include <string>

class PacketCapture {
public:
    void startCapture(const std::string& interface);
};
