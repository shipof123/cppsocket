# Callbacks

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
