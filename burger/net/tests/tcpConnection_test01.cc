#include "burger/net/TcpServer.h"
#include "burger/net/EventLoop.h"
#include "burger/net/InetAddress.h"
#include <iostream>

using namespace burger;
using namespace burger::net;

void onConnection(const TcpConnectionPtr& conn) {
    if(conn->isConnected()) {
        std::cout << "onConnection(): new connection [" 
            << conn->getName() <<  "] from " 
            << conn->getPeerAddress().getIpPortStr() << std::endl;
    } else {
        std::cout << "onConnection() : connection " 
            << conn->getName() << " is down" << std::endl;
    }   
}

void onMessage(const TcpConnectionPtr& conn, 
                Buffer& buf, 
                Timestamp recieveTime) {
    std::cout << "onMessage(): received " << buf.getReadableBytes() 
        << " bytes from connection " << conn->getName() 
        << " at " << recieveTime.toFormatTime() <<std::endl;
    std::cout << "onMessage() : " << buf.retrieveAllAsString() << std::endl;
}   

int main() {
    // if (!Logger::Instance().init("log", "logs/test.log", spdlog::level::trace)) {
    //     std::cout << "Logger init error" << std::endl;
	// 	return 1;
	// }
    std::cout << "main() : pid = " << ::getpid() << std::endl;
    InetAddress listenAddr(8888);
    EventLoop loop;
    TcpServer server(&loop, listenAddr, "TcpServer");
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.start();

    loop.loop();
}