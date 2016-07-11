//
//  rtmp_relay
//

#include <algorithm>
#include <iostream>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include "Network.h"
#include "Socket.h"

Network::Network()
{
    
}

bool Network::update()
{
    std::vector<pollfd> pollFds;
    pollFds.reserve(sockets.size());
    
    std::map<int, std::reference_wrapper<Socket>> socketMap;
    
    for (auto socket : sockets)
    {
        pollfd pollFd;
        pollFd.fd = socket.get().socketFd;
        pollFd.events = POLLIN;

        if (socket.get().isConnecting() || socket.get().hasOutData())
        {
            pollFd.events |= POLLOUT;
        }
        
        pollFds.push_back(pollFd);
        
        socketMap.insert(std::pair<uint32_t, std::reference_wrapper<Socket>>(socket.get().socketFd, socket));
    }
    
    if (poll(pollFds.data(), static_cast<nfds_t>(pollFds.size()), 0) < 0)
    {
        int error = errno;
        std::cerr << "Poll failed, error: " << error << std::endl;
        return false;
    }
    
    for (uint32_t i = 0; i < pollFds.size(); ++i)
    {
        pollfd pollFd = pollFds[i];

        auto iter = socketMap.find(pollFd.fd);
        
        if (iter != socketMap.end())
        {
            if (pollFd.revents & POLLIN)
            {
                iter->second.get().read();
            }

            if (pollFd.revents & POLLOUT)
            {
                iter->second.get().write();
            }
        }
    }
    
    return true;
}

void Network::addSocket(Socket& socket)
{
    sockets.push_back(socket);
}

void Network::removeSocket(Socket& socket)
{
    std::vector<std::reference_wrapper<Socket>>::iterator i = std::find_if(sockets.begin(), sockets.end(), [&socket](const std::reference_wrapper<Socket>& sock) { return &socket == &sock.get(); });
    
    if (i != sockets.end())
    {
        sockets.erase(i);
    }
}