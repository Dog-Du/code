#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    try
    {
        // 创建一个socket对象
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            throw std::runtime_error("socket creation failed");
        }

        // 定义服务器的地址和端口号
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(30000);
        serv_addr.sin_addr.s_addr = inet_addr("47.93.236.205");

        // 连接到服务器
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
        {
            throw std::runtime_error("connection failed");
        }

        // 要发送的文字
        std::string message = "22114514木更的狗";

        // 发送数据
        send(sock, message.c_str(), message.length(), 0);

        // 关闭socket
        close(sock);
    }
    catch (std::exception& e)
    {
        // 打印异常信息
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
