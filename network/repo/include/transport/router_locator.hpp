#ifndef NETWORK_ROUTERLOCATOR_HPP
#define NETWORK_ROUTERLOCATOR_HPP

namespace network {

class Router;

struct RouterLocator
{
    static Router* getRouter();
    static void provide( Router* router );
};

}

#endif // NETWORK_ROUTERLOCATOR_HPP
