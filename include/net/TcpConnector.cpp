#include "net/TcpConnector.h"
#include "net/EventLoop.h"
#include "base/ZLog.h"
#include "net/Channel.h"
NAMESPACE_ZL_NET_START

TcpConnector::TcpConnector(EventLoop *loop, const InetAddress& serverAddr)
    : state_(kDisconnected), connect_(false), 
      loop_(loop), serverAddr_(serverAddr),
      TcpConnector_channel_(NULL)
{

}

TcpConnector::~TcpConnector()
{

}

void TcpConnector::connect()
{
     connect_ = true;
     loop_->runInLoop(std::bind(&TcpConnector::connectInLoop, this));
}

void TcpConnector::connectInLoop()
{
    loop_->assertInLoopThread();
    assert(state_ == kDisconnected);
    if (connect_)
    {
        connectServer();
    }
}

void TcpConnector::connectServer()
{
    ZL_SOCKET sockfd = SocketUtil::createSocket(); //::createNonblockingOrDie();
    SocketUtil::setNonBlocking(sockfd);

    int ret = SocketUtil::connect(sockfd, serverAddr_.getSockAddrInet());
    int savedErrno = (ret == 0) ? 0 : errno;
    switch (savedErrno)
    {
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
        connectEstablished(sockfd);
        break;

    case EAGAIN:
    case EADDRINUSE:
    case EADDRNOTAVAIL:
    case ECONNREFUSED:
    case ENETUNREACH:
        //retry(sockfd);
        break;

    case EACCES:
    case EPERM:
    case EAFNOSUPPORT:
    case EALREADY:
    case EBADF:
    case EFAULT:
    case ENOTSOCK:
        LOG_ERROR("TcpConnector::connectServer() error[%d]", savedErrno);
        SocketUtil::closeSocket(sockfd);
        break;

    default:
        LOG_ERROR("TcpConnector::connectServer() unexpected error[%d]", savedErrno);
        SocketUtil::closeSocket(sockfd);
        // connectErrorCallback_();
        break;
    }
}

void TcpConnector::connectEstablished(ZL_SOCKET sock)
{
    LOG_INFO("TcpConnector::connectEstablished : [%d]", sock);
    setState(kConnecting);
    // assert(!TcpConnector_channel_);
    if(TcpConnector_channel_)
        delete TcpConnector_channel_;
    TcpConnector_channel_ = new Channel(loop_, sock);

    TcpConnector_channel_->setWriteCallback(std::bind(&TcpConnector::handleWrite, this));
    TcpConnector_channel_->setErrorCallback(std::bind(&TcpConnector::handleError, this));

    TcpConnector_channel_->enableWriting();
}

void TcpConnector::stop()
{
    connect_ = false;
    loop_->queueInLoop(std::bind(&TcpConnector::stopInLoop, this));
}

void TcpConnector::stopInLoop()
{
    loop_->assertInLoopThread();
    if (state_ == kConnecting)
    {
        setState(kDisconnected);
        ZL_SOCKET sockfd = disableChannel();
        retry(sockfd);
    }
}

ZL_SOCKET TcpConnector::disableChannel()
{
    TcpConnector_channel_->disableAll();   // ��poller���Ƴ������ٹ�ע�κ��¼�
    TcpConnector_channel_->remove();
    ZL_SOCKET sockfd = TcpConnector_channel_->fd();
    return sockfd;
}

//����Զ��socket�ɹ�
void TcpConnector::handleWrite()
{
    if (state_ == kConnecting) //���ӽ���ʱע��Channel��д�¼�����ʱ��Ӧ��д����socket���أ�������Channel
    {
        ZL_SOCKET sockfd = disableChannel();
        int err = SocketUtil::getSocketError(sockfd);
        if (err)
        {
            LOG_WARN("TcpConnector::handleWrite - SO_ERROR = [%d][%d][%s]", sockfd, err, strerror(err));
            retry(sockfd);
        }
        else if (SocketUtil::isSelfConnect(sockfd))
        {
            LOG_WARN("TcpConnector::handleWrite - Self connect = [%d]", sockfd);
            retry(sockfd);
        }
        else
        {
            setState(kConnected);
            if (connect_)
            {
                newConnCallBack_(sockfd);
            }
            else
            {
                SocketUtil::closeSocket(sockfd);
            }
        }
    }
    else
    {
        assert(state_ == kDisconnected);
    }
}

void TcpConnector::handleError()
{
    LOG_ERROR("TcpConnector::handleError(): fd = [%d], state = [%d]", TcpConnector_channel_->fd(), state_);
    if (state_ == kConnecting)
    {
        ZL_SOCKET sockfd = disableChannel();
        int err = SocketUtil::getSocketError(sockfd);
        LOG_ERROR("TcpConnector::handleError() SO_ERROR = [%d][%s]", err, strerror(err));
        retry(sockfd);
    }
}

void TcpConnector::retry(ZL_SOCKET sockfd)
{
    SocketUtil::closeSocket(sockfd);
    setState(kDisconnected);
    if (connect_)
    {
        LOG_INFO("TcpConnector::retry; Retry connecting to [%s]", serverAddr_.ipPort().c_str());
        loop_->runInLoop(std::bind(&TcpConnector::connectInLoop, this));
    }
    else
    {
         LOG_INFO("TcpConnector::retry: do not connect");
    }
}

NAMESPACE_ZL_NET_END
