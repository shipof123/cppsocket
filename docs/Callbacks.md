# Callbacks

## Successful Connections


```cpp
  void setAcceptCallback(const std::function<void(Socket&, Socket&)>& newAcceptCallback)
```
Description:
  Function Executed when connection is accepted.

ex:
```cpp 
  
```
---
```cpp
  void setReadCallback(const std::function<void(Socket&, const std::vector<uint8_t>&)>& newReadCallback)
```
Description:

Function that accepts information read by the the socket.  
Executed upon reciveal of information

ex:
```cpp
  client.setReadCallback([](cppsocket::Socket& socket, const std::vector<uint8_t>& data) {
         std::cout << "Got data: " << data.data() << " from " << cppsocket::ipToString(socket.getRemoteIPAddress()) << std::endl;
  });
```
---
```cpp
```
Description:  

ex:
```cpp
```
---
```cpp
  void setCloseCallback(const std::function<void(Socket&)>& newCloseCallback)
```
---
## Error Handling

```cpp
void setConnectErrorCallback(const std::function<void(Socket&)>& newConnectErrorCallback)
```
Set Callback for Connection Errors  
ex:  
```cpp
  client.setConnectErrorCallback([&client, address](cppsocket::Socket& socket) {
      std::cout << "Failed to connected to " << cppsocket::ipToString(socket.getRemoteIPAddress()) << std::endl;
      client.connect(address);
   });
```
