//
//  cppsocket
//

#pragma once

#include <vector>
#include <functional>
#include <cstdint>
#include <string>

#ifdef _MSC_VER
#define NOMINMAX
#include <winsock2.h>
typedef SOCKET socket_t;
#else
#include <errno.h>
typedef int socket_t;
#define INVALID_SOCKET -1
#endif

namespace cppsocket
{
    const uint32_t ANY_ADDRESS = 0;

    inline std::string ipToString(uint32_t ip)
    {
        uint8_t* ptr = reinterpret_cast<uint8_t*>(&ip);

        return std::to_string(static_cast<uint32_t>(ptr[0])) + "." +
        std::to_string(static_cast<uint32_t>(ptr[1])) + "." +
        std::to_string(static_cast<uint32_t>(ptr[2])) + "." +
        std::to_string(static_cast<uint32_t>(ptr[3]));
    }

    inline int getLastError()
    {
#ifdef _MSC_VER
        return WSAGetLastError();
#else
        return errno;
#endif
    }

    class Network;
    class Acceptor;

    class Socket
    {
        friend Network;
        friend Acceptor;
    public:
        Socket(Network& aNetwork);
        virtual ~Socket();

        Socket(const Socket&) = delete;
        Socket& operator=(const Socket&) = delete;

        Socket(Socket&& other);
        Socket& operator=(Socket&& other);

        virtual bool close();
        virtual void update(float delta);

        bool startRead();
        void setReadCallback(const std::function<void(Socket&, const std::vector<uint8_t>&)>& newReadCallback);
        void setCloseCallback(const std::function<void(Socket&)>& newCloseCallback);

        bool send(std::vector<uint8_t> buffer);

        uint32_t getLocalIPAddress() const { return localIPAddress; }
        uint16_t getLocalPort() const { return localPort; }

        uint32_t getRemoteIPAddress() const { return remoteIPAddress; }
        uint16_t getRemotePort() const { return remotePort; }

        bool isBlocking() const { return blocking; }
        bool setBlocking(bool newBlocking);

        bool isReady() const { return ready; }

        bool hasOutData() const { return !outData.empty(); }

    protected:
        Socket(Network& aNetwork, socket_t aSocketFd, bool aReady,
               uint32_t aLocalIPAddress, uint16_t aLocalPort,
               uint32_t aRemoteIPAddress, uint16_t aRemotePort);

        virtual bool read();
        virtual bool write();

        bool readData();
        bool writeData();

        virtual bool disconnected();

        bool createSocketFd();
        bool closeSocketFd();
        bool setFdBlocking(bool block);

        Network& network;

        socket_t socketFd = INVALID_SOCKET;

        bool ready = false;
        bool blocking = true;

        uint32_t localIPAddress = 0;
        uint16_t localPort = 0;

        uint32_t remoteIPAddress = 0;
        uint16_t remotePort = 0;

        std::function<void(Socket&, const std::vector<uint8_t>&)> readCallback;
        std::function<void(Socket&)> closeCallback;

        std::vector<uint8_t> inData;
        std::vector<uint8_t> outData;
    };
}
