#ifndef NETWORK_TRANSPORT_ROUTER_HPP
#define NETWORK_TRANSPORT_ROUTER_HPP

#include <network/status.hpp>

namespace network {

class Request;
class Response;

class Router
{
public:
    virtual ~Router() {}
    virtual void init() = 0;
    virtual void destroy() = 0;
    virtual util::Status perform( Request& request, Response* response ) = 0;
};

}

#endif // NETWORK_TRANSPORT_ROUTER_HPP
