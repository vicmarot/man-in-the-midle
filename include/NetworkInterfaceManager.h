#pragma once

#include <vector>
#include <string>

class NetworkInterface {
public:
    std::string name;
    std::string description;

    NetworkInterface(const std::string& name, const std::string& description)
        : name(name), description(description) {}
};

class NetworkInterfaceManager {
public:
    NetworkInterfaceManager() = default;
    std::vector<NetworkInterface> getAvailableInterfaces();
    void printInterfaces(const std::vector<NetworkInterface>& interfaces);
    int selectInterface(const std::vector<NetworkInterface>& interfaces);
};
