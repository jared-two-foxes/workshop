#ifndef NETWORK_NETWORKMANAGER_HPP__
#define NETWORK_NETWORKMANAGER_HPP__

#include <network/Request.hpp>
#include <network/Response.hpp>

namespace network {

class NetworkManager
{
private:
    class RequestRouter* m_router;

public:
    void init();
    void destroy();

    Response* performRequest( Request* request );

};

}

#endif // SCHEDULE_NETWORK_HPP__
