#include "net/Socket.h"
#include "base/Exception.h"
#include "net/InetAddress.h"
NAMESPACE_ZL_NET_START

const static int MAX_RECV_SIZE = 64*1024;  // 设置64k ?

/*********
recv read write send 函数的返回值说明:
	< 0 ：出错;
	= 0 ：连接关闭;
	> 0 : 接收/发送数据大小
除此之外，非阻塞模式下返回值 < 0 并且 (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况下认为连接是正常的，继续接收/发送
*********/

Socket::Socket(ZL_SOCKET fd) : sockfd_(fd) 
{
}

Socket::~Socket()
{
    SocketUtil::closeSocket(sockfd_);
}

bool Socket::bind(const char* ip, int port)
{
    if(!isValid())
    {
        return false;
    }

    return SocketUtil::bind(sockfd_, ip, port) == 0;
}

bool Socket::bind(const InetAddress& addr)
{
    if (!isValid())
    {
        return false;
    }
    return SocketUtil::bind(sockfd_, addr.getSockAddrInet()) == 0;
}

bool Socket::listen(int backlog /*= 5*/) const
{
    if(!isValid())
    {
        return false;
    }

    int ret = ZL_LISTEN(sockfd_, backlog);
    if(ret == -1)
    {
        return false;
    }
    return true;
}

ZL_SOCKET Socket::accept(ZL_SOCKADDR_IN* peerAddr) const
{
    return SocketUtil::accept(sockfd_, peerAddr);
}

ZL_SOCKET Socket::accept(InetAddress* peerAddr) const
{
    ZL_SOCKADDR_IN addr;
    ::memset(&addr, 0, sizeof(addr));
    ZL_SOCKET connfd = SocketUtil::accept(sockfd_, &addr);
    if (connfd > 0)
    {
        peerAddr->setSockAddrInet(addr);
    }
    return connfd;
}

bool Socket::connect(const char* ip, int port)
{
    if (!isValid())
    {
        return false;
    }

    return SocketUtil::connect(sockfd_, ip, port) == 0;
}

void Socket::close()
{
    if (isValid())
    {
        ZL_CLOSE(sockfd_);
    }
}

int Socket::send(const std::string& data) const
{
    return send(data.c_str(), data.size());
}

int Socket::send(const void* data, size_t size)const
{
    int len = ZL_SEND(sockfd_, data, size, 0);
    //if (len == -1)     // error
    //else if (len == 0) // connection is closed
    //else               // ok
    return len;
}

int Socket::recv(std::string& data) const
{
    char buf[MAX_RECV_SIZE + 1] = { 0 };

    while(true)
    {
        int len = recv(buf, MAX_RECV_SIZE, false);
        if(len == 0)  // 连接已关闭
        {
            return 0;
        }
        else if(len < 0)
        {
            if(SOCK_ERR_RW_RETRY(SOCKET_ERROR))
                continue;
            else if(SOCKET_ERROR == SOCK_ERR_EWOULDBLOCK)
                break;
            else
                return len; // 发生了错误
            break;
        }
        else
        {
            data.insert(data.end(), buf, buf + len);
            if(len < MAX_RECV_SIZE)   //全部接收完成
                break;
        }
    }
    return data.size();
}

int Socket::recv(void* data, int length, bool complete /*= false */) const
{
    int received = 0;
    if(complete)
    {
        while(received != length)
        {
            int len = ZL_RECV(sockfd_, (char *)data + received, length - received, 0);
            if(len == -1)
            {
                printf("status == -1, errno == [%d], in Socket::recv\n", errno);
                return len;
            }
            else if(len == 0)
            {
                return len;
            }
            else
            {
                received += len;
            }
        }
    }
    else
    {
        received = ZL_RECV(sockfd_, (char *)data, length, 0);
    }
    return received;
}

int Socket::sendTo(const std::string& data, int flags, InetAddress& sinaddr)const
{
    return sendTo(data.c_str(), data.size(), flags, sinaddr);
}

int Socket::sendTo(const void* data, size_t size, int flags, InetAddress& sinaddr)const
{
    int len = ZL_SENDTO(sockfd_, data, size, flags, sinaddr, sinaddr.addressLength());

    return len;
}

int Socket::recvFrom(std::string& data, int flags, InetAddress& sinaddr)const
{
    char buf[MAX_RECV_SIZE + 1] = { 0 };

    while(true)
    {
        int len = recvFrom(buf, MAX_RECV_SIZE, flags, sinaddr);
        if(len == -1 || len == 0)
            break;
        data.insert(data.end(), buf, buf + len);
        if(len < MAX_RECV_SIZE)
            break;
    }
    return data.size();
}

int Socket::recvFrom(void* data, int length, int flags, InetAddress& sinaddr)const
{
    socklen_t slen;
    int len = ZL_RECVFROM(sockfd_, data, length, flags, sinaddr, &slen);
    if(slen != sinaddr.addressLength())
        throw zl::base::Exception("unknown protocol type(in Socket::RecvFrom)");
    return len;
}

bool Socket::setNonBlocking(bool on /*= true*/)
{
    SocketUtil::setNonBlocking(sockfd_, on);
    return true;
}

bool Socket::setNoDelay(bool on /*= true*/)
{
    return SocketUtil::setNoDelay(sockfd_, on) == 0;
}

bool Socket::setReuseAddr(bool on /*= true*/)
{
    return SocketUtil::setReuseAddr(sockfd_, on) == 0;
}

bool Socket::setKeepAlive(bool on /*= true*/)
{
    return SocketUtil::setKeepAlive(sockfd_, on) == 0;
}

bool Socket::setSendBuffer(int size)
{
    return SocketUtil::setSendBuffer(sockfd_, size) == 0;
}
      
bool Socket::getSendBuffer(int* size)
{
    return SocketUtil::getSendBuffer(sockfd_, size) == 0;
}

bool Socket::setRecvBuffer(int size)
{
    return SocketUtil::setRecvBuffer(sockfd_, size) == 0;
}

bool Socket::getRecvBuffer(int* size)
{
    return SocketUtil::getRecvBuffer(sockfd_, size) == 0;
}

bool Socket::setSendTimeout(long long timeoutMs)
{
    return SocketUtil::setSendTimeout(sockfd_, timeoutMs) == 0;
}

bool Socket::getSendTimeout(long long* timeoutMs)
{
    return SocketUtil::getSendTimeout(sockfd_, timeoutMs) == 0;
}

bool Socket::setRecvTimeout(long long timeoutMs)
{
    return SocketUtil::setRecvTimeout(sockfd_, timeoutMs) == 0;
}

bool Socket::getRecvTimeout(long long* timeoutMs)
{
    return SocketUtil::getRecvTimeout(sockfd_, timeoutMs) == 0;
}

bool Socket::setLinger(bool enable, int waitTimeSec /*= 5*/)
{
    linger lngr;
    lngr.l_onoff = enable ? 1 : 0;
    lngr.l_linger = waitTimeSec;

    return ZL_SETSOCKOPT(sockfd_, SOL_SOCKET, SO_LINGER, &lngr, sizeof(linger)) == 0;
}

bool Socket::getLinger(bool& enable, int& waitTimeSec)
{
    linger lngr;
    if(ZL_GETSOCKOPT(sockfd_, SOL_SOCKET, SO_RCVTIMEO, &lngr, sizeof(lngr)) == 0)
    {
        enable = lngr.l_onoff;
        waitTimeSec = lngr.l_linger;
        return true;
    }
    return false;
}

NAMESPACE_ZL_NET_END
