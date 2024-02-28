cmake_minimum_required(VERSION 3.10)
project(MitM VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP libpcap)
# pkg_check_modules(LIBNET libnet)


include_directories(${PCAP_INCLUDE_DIRS} ${LIBNET_INCLUDE_DIRS})

add_definitions(${PCAP_CFLAGS_OTHER} ${LIBNET_CFLAGS_OTHER})

set(SOURCES
    src/main.cpp
    src/PacketCapture.cpp
    src/NetworkInterfaceManager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${PCAP_LIBRARIES} ${LIBNET_LIBRARIES})

link_directories(${PCAP_LIBRARY_DIRS} ${LIBNET_LIBRARY_DIRS})
