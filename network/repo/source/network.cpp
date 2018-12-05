#include <network/network.hpp>

#include <network/transport/router_locator.hpp>

#include <network/curl_router.hpp>

using namespace network;

Router* g_router = nullptr;

void network::init()
{
    g_router = new CurlRouter();
    g_router->init();
}

void network::destroy()
{
    RouterLocator::provide( nullptr );
    if (g_router)
    {
      g_router->destroy();
      delete g_router;
    }
}


Router* RouterLocator::getRouter() {
    return g_router;
}

void RouterLocator::provide( Router* router ) {
    g_router = router;
}
