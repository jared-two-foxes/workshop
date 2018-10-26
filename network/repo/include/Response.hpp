#ifndef NETWORK_RESPONSE_HPP__
#define NETWORK_RESPONSE_HPP__

#include <string>

namespace network {

class Response
{
public:
    std::string buffer;

public:
    void Write( std::string& s ) {
        buffer.append( s );
    }
};

}

#endif // NETWORK_RESPONSE_HPP__
