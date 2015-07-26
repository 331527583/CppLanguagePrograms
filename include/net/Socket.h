﻿// ***********************************************************************
// Filename         : Socket.h
// Author           : LIZHENG
// Created          : 2014-07-01
// Description      : socket的跨平台包装, 以RAII的方式管理socket fd
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SOCKET_H
#define ZL_SOCKET_H
#include "base/NonCopy.h"
#include "net/SocketUtil.h"
NAMESPACE_ZL_NET_START

class SocketAddress;
class InetAddress;

class Socket : zl::NonCopy
{
public:
    explicit Socket(ZL_SOCKET fd);
    ~Socket();

public:
    // Server Initialization
    bool           bind(const char *ip, int port);
    bool           bind(const InetAddress& addr); 
    bool           listen(int backlog = 5) const;
    ZL_SOCKET      accept(ZL_SOCKADDR_IN* peerAddr) const;
    ZL_SOCKET      accept(InetAddress *peerAddr) const;
    void           close();

    // Client Initialization
    bool           connect(const char* ip, const int port);

    // Socket Settings
    /** Enable/disable Block Socket */
    bool           setNonBlocking(bool on = true);

    /** Enable/disable TCP_NODELAY(enable/disable Nagle's algorithm) */
    bool           setNoDelay(bool on = true);

    /** Enable/disable SO_REUSEADDR(TIME_WAIT) */
    bool           setReuseAddr(bool on = true);

    /** Enable/disable SO_KEEPALIVE */
    bool           setKeepAlive(bool on = true);

    /** Set/Get SO_SNDBUF */
    bool           setSendBuffer(int size);
    bool           getSendBuffer(int* size);

    /** Set/Get  SO_RCVBUF */
    bool           setRecvBuffer(int size);
    bool           getRecvBuffer(int* size);

    /** Set/Get  SO_SNDTIMEO */
    bool           setSendTimeout(long long timeoutMs);
    bool           getSendTimeout(long long* timeoutMs);

    /** Set/Get  SO_RCVTIMEO */
    bool           setRecvTimeout(long long timeoutMs);
    bool           getRecvTimeout(long long* timeoutMs);

    /** Set/Get  SO_LINGER */
    bool           setLinger(bool enable, int waitTimeSec = 5);
    bool           getLinger(bool& enable, int& waitTimeSec);

    // Net Transimission
    int            send(const std::string& data) const;
    int            send(const void* data, size_t size)const;
    int            recv(std::string& data) const;
    int            recv(void* data, int length, bool complete = false)const;
    int            sendTo(const std::string& data, int flags, InetAddress& sinaddr)const;
    int            sendTo(const void* data, size_t size, int flags, InetAddress& sinaddr)const;
    int            recvFrom(std::string& data, int flags, InetAddress& sinaddr)const;
    int            recvFrom(void* data, int length, int flags, InetAddress& sinaddr)const;

    // Property Access
    bool           isValid() const
    {
        return sockfd_ != ZL_INVALID_SOCKET;
    }

    const ZL_SOCKET& fd() const
    {
        return sockfd_;
    }

    //template < typename T >
    //Socket& operator<< (const T& t)
    //{
        // t must be pod
    //    send(&t, sizeof(t));
    //}

    //template < typename T >
    //Socket& operator>> (const T& t)
    //{
    //    // t must be pod
    //    recv(&t, sizeof(t));
    //}
protected:
    const ZL_SOCKET sockfd_;
};

NAMESPACE_ZL_NET_END
#endif  /* ZL_SOCKET_H */
