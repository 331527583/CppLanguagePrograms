// ***********************************************************************
// Filename         : TcpAcceptor.h
// Author           : LIZHENG
// Created          : 2014-10-26
// Description      : ����˽�������������ĳһ�˿��ϣ�����Զ��Socket����
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-12-22
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_TCPACCEPTOR_H
#define ZL_TCPACCEPTOR_H
#include "Define.h"
#include "base/Timestamp.h"
#include "base/NonCopy.h"
NAMESPACE_ZL_NET_START
class Socket;
class InetAddress;
class Channel;
class EventLoop;
using zl::base::Timestamp;

class TcpAcceptor : zl::NonCopy
{
public:
    //typedef std::function<void(Socket *)> NewConnectionCallback;
    typedef std::function<void (int , const InetAddress&)> NewConnectionCallback;
public:
    TcpAcceptor(EventLoop *loop, const InetAddress& listenAddr);
    ~TcpAcceptor();

    void setNewConnectionCallback(const NewConnectionCallback& callback)
    {
        newConnCallBack_ = callback;
    }

    void listen();

private:
    void onAccept(Timestamp now);

private:
    EventLoop *loop_;
    Socket    *accept_socket;
    Channel   *accept_channel_;
    NewConnectionCallback newConnCallBack_;
};

NAMESPACE_ZL_NET_END
#endif  /* ZL_TCPACCEPTOR_H */
