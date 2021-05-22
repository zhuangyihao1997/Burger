#ifndef COTCPCONNECTION_H
#define COTCPCONNECTION_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <boost/any.hpp>

#include "InetAddress.h"
#include "RingBuffer.h"
#include "Callbacks.h"

namespace burger {
namespace net {

class IBuffer;
class Socket;
class Processor;
// todo : 写成继承的形式

class CoTcpConnection : boost::noncopyable {
public:
    using ptr = std::shared_ptr<CoTcpConnection>;
    CoTcpConnection(Processor* proc,
            int sockfd, 
            const InetAddress& localAddr,
            const InetAddress& peerAddr,
            const std::string& connName);
    ~CoTcpConnection();
    // todo : more operation
    ssize_t recv(RingBuffer::ptr buf);
    void send(RingBuffer::ptr buf);
    void send(const std::string& msg);
    void send(const char* start, size_t sendSize);  

    void send(RingBuffer::ptr buf, size_t sendSize);
    const InetAddress& getLocalAddress() const { return localAddr_; }
    const InetAddress& getPeerAddr() const { return peerAddr_; }
    const std::string& getName() const { return connName_; }
    void setTcpNoDelay(bool on);
    bool isConnected() const { return !quit_; }

    void shutdown();
    // void close();
private: 
    void sendInProc(const char* start, size_t sendSize);
private:
    Processor* proc_;
    std::unique_ptr<Socket> socket_;
    const InetAddress localAddr_;
    const InetAddress peerAddr_;
    const std::string connName_;
    bool quit_;
};



} // namespace net

} // namespace burger






#endif // COTCPCONNECTION_H