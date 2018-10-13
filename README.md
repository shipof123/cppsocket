# cppsocket 
C++ socket wrapper

# Description

Cppsocket is a cross-platform Header only library that uses callback functions to process data  

# Usage:
## Table of contents for /docs
 - [Callbacks](/docs/Callbacks.md)


# Making A simple TCP Client:
Includes
```cpp
#include <iostream>
#include <string>
#include "Socket.hpp"
```
Setting up host
```cpp
int main() {
  if(argc < 3) {
    std::cerr << "Usage: " << argv[0] << "  [hostname] [port]" << std::endl;
    return EXIT_FAILURE;
  }
  const std::vector<uint8_t> msg = {'H','e','l','l','o',' ','W','o','r','l','d'};
  const std::string host = argv[1];
  
  
  cppsocket::Network network;  
  cppsocket::Socket client(network);
  
  client.setBlocking(false);
  client.setConnectTimeout(2.0f);
``` 
Connect to server and set up [callback functions](/docs/Callbacks.md)

```cpp
  client.connect(host);
  
  client.setReadCallback([](const cppsocket::Socket& Server, const std::vector<uint8_t> data){
    std::cout <<
       "Recieved data: " << data.data() << " from: " << cppsocket::ipToString(socket.getRemoteIPAddress())
    << std::endl;
  });
  
}
```
