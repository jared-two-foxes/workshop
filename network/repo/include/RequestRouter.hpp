#ifndef NETWORK_REQUESTROUTER_HPP
#define NETWORK_REQUESTROUTER_HPP

namespace network {

class Request;
class Response;

class RequestRouter
{
public:
    virtual ~RequestRouter() {}
    virtual void init() = 0;
    virtual void destroy() = 0;
    virtual Response* perform( Request* request ) = 0;

    //void setCallback( size_t (*fn)(void*, size_t, size_t, void*), void* data );
};

}

#endif // NETWORK_REQUESTROUTER_HPP
