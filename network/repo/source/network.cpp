#include <network/network.hpp>

#include <network/transport/router_locator.hpp>

#include <network/curl_router.hpp>

using namespace network;

Router* g_router = nullptr;

void network::init()
{
    g_router = new CurlRouter();
}

void network::destroy()
{
    RouterLocator::provide( nullptr );
    delete g_router;
}


Router* RouterLocator::getRouter() {
    return g_router;
}

void RouterLocator::provide( Router* router ) {
    g_router = router;
}
