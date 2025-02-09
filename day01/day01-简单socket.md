# day01-简单socket

---

## server.cpp

---

### 功能概述：

1. **创建一个 TCP 服务器**，监听本地指定端口（8080）。
2. **接受客户端连接**，打印客户端的 IP 地址和端口信息。
3. **关闭连接并退出**。

---

### 代码关键点解析：

1. **宏定义：**
   
   ```cpp
   #define PORT 8080
   ```
   
   - 定义了服务器监听的端口号 `8080`。

2. **头文件包含：**
   
   - 包含了实现网络通信所需的头文件，例如 `sys/socket.h`（套接字接口），`arpa/inet.h`（地址转换函数）。

3. **变量声明和初始化：**
   
   ```cpp
   sockaddr_in seraddr, cliaddr;
   memset(&seraddr, 0, sizeof(seraddr));
   memset(&cliaddr, 0, sizeof(cliaddr));
   ```
   
   - 定义并初始化服务器地址和客户端地址结构体 `sockaddr_in`。
   - `sockaddr_in` 是用于存储 IP 地址和端口号的结构体。

4. **设置服务器地址信息：**
   
   ```cpp
   seraddr.sin_family = AF_INET;
   seraddr.sin_addr.s_addr = INADDR_ANY;
   seraddr.sin_port = htons(PORT);
   ```
   
   - `sin_family = AF_INET`：指定使用 IPv4 地址族。
   - `sin_addr.s_addr = INADDR_ANY`：监听本地所有可用的网络接口。
   - `htons(PORT)`：将端口号转换为网络字节序（大端格式）。

5. **创建套接字：**
   
   ```cpp
   int serfd = socket(AF_INET, SOCK_STREAM, 0);
   ```
   
   - 使用 `socket` 函数创建一个 TCP 套接字（SOCK_STREAM 表示 TCP 协议）。
   - 若返回值为 `-1`，表示创建失败。

6. **绑定套接字到指定地址：**
   
   ```cpp
   bind(serfd, (sockaddr*)&seraddr, sizeof(seraddr))
   ```
   
   - 将套接字绑定到本地的 IP 地址和端口号。
   - 若绑定失败，程序会打印错误信息并退出。

7. **开始监听：**
   
   ```cpp
   listen(serfd, SOMAXCONN);
   ```
   
   - 将套接字设置为监听状态。
   - `SOMAXCONN` 表示可以接受的最大连接数（系统默认值）。

8. **接受客户端连接：**
   
   ```cpp
   int clifd = accept(serfd, (sockaddr*)&cliaddr, &clilen);
   ```
   
   - `accept` 函数阻塞等待客户端连接。
   - 若有客户端连接成功，返回一个新的套接字文件描述符 `clifd`，用于与该客户端通信。
   - 同时，`cliaddr` 存储了客户端的 IP 地址和端口信息。

9. **打印客户端信息：**
   
   ```cpp
   printf("fd:%d\nip:%s\nport:%d\n", clifd, inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
   ```
   
   - 打印客户端的：
     - 文件描述符 `clifd`。
     - IP 地址（通过 `inet_ntoa` 将网络字节序转为可读字符串）。
     - 端口号（通过 `ntohs` 将网络字节序转为主机字节序）。

10. **关闭套接字：**
    
    ```cpp
    close(clifd);
    close(serfd);
    ```
    
    - 关闭客户端套接字和服务器套接字，释放资源。

---

### 程序流程总结：

1. 创建套接字；
2. 绑定地址和端口；
3. 开始监听；
4. 接受客户端连接；
5. 打印客户端信息；
6. 关闭套接字，结束程序。

---

## client.cpp

---

### 代码总结：

1. **定义端口号**：
   
   - 使用宏 `#define PORT 8080` 定义了目标通信的端口号（8080）。

2. **创建 `sockaddr_in` 结构体**：
   
   - 定义并初始化 `sockaddr_in` 结构体变量 `serv_addr`，用于存储服务器的地址信息（包括 IP 地址和端口）。
   - 设置地址族为 `AF_INET`（IPv4）。
   - 设置目标 IP 地址为 `127.0.0.1`（本地回环地址）。
   - 设置目标端口为 `8080`（通过 `htons()` 将端口号转换为网络字节序）。

3. **创建套接字**：
   
   - 使用 `socket()` 函数创建一个 TCP 套接字（`SOCK_STREAM` 表示使用流式套接字，TCP 协议）。
   - 如果创建失败，打印错误信息并退出程序。

4. **连接服务器**：
   
   - 使用 `connect()` 函数将客户端套接字连接到目标服务器（`127.0.0.1:8080`）。
   - 如果连接失败，打印错误信息并退出程序。

5. **关闭套接字**：
   
   - 使用 `close()` 函数关闭套接字，释放资源。

6. **程序退出**：
   
   - 正常返回 `0`，表示程序执行成功。

---

### 功能总结：

这段代码实现了一个简单的 TCP 客户端，向本地服务器（`127.0.0.1`）的端口 `8080` 发起连接。如果连接成功，程序会立即关闭套接字并退出；如果连接失败或套接字创建失败，会打印错误信息并退出。

---

### 注意事项：

1. **依赖的服务器端**：
   
   - 客户端连接的目标需要有一个运行在 `127.0.0.1:8080` 的服务器，否则 `connect()` 会失败。

2. - 代码中没有实现数据发送和接收的逻辑。如果需要实现完整的通信功能，需要使用 `send()` 和 `recv()` 函数进行数据交互。
