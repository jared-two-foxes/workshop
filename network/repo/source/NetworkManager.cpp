
#include <network/NetworkManager.hpp>
#include <network/CurlRequestRouter.hpp>

#include <assert.h>

using namespace network;

void NetworkManager::init()
{
    m_router = new CurlRequestRouter();
    m_router->init();
}

void NetworkManager::destroy()
{
    if ( m_router )
    {
        m_router->destroy();
        delete m_router;
        m_router = nullptr;
    }
}

Response* NetworkManager::performRequest( Request* request )
{
    assert( m_router );
    return m_router->perform( request );
}
