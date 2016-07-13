//
//  cppsocket
//

#pragma once

#include <functional>
#include "Socket.h"

namespace cppsocket
{
    class Connector: public Socket
    {
    public:
        Connector(Network& network);
        virtual ~Connector();

        Connector(Connector&& other);
        Connector& operator=(Connector&& other);

        bool connect(const std::string& address, uint16_t newPort = 0);
        bool connect(uint32_t address, uint16_t newPort);

        void setConnectCallback(const std::function<void()>& newConnectCallback);
    
    protected:
        virtual bool write();
    
        std::function<void()> connectCallback;
    };
}
