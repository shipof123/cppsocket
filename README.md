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
  if(argc < 2) {
    std::cerr << "Usage: " << argv[0] << "  [hostname]" << std::endl;
    return EXIT_FAILURE;
  }
  std::string host = argv[1];
  
  cppsocket::Network network;  
  cppsocket::Socket client(network);
  
  client.setBlocking(false);
  client.setConnectTimeout(2.0f);
  client.connect(host);

``` 
Set up callback functions

```cpp
  
}
```
